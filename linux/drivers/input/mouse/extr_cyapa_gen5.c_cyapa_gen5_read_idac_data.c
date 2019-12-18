#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct pip_app_cmd_head {scalar_t__* parameter_data; scalar_t__ cmd_code; int /*<<< orphan*/  report_id; scalar_t__ length; scalar_t__ addr; } ;
struct cyapa {int aligned_electrodes_rx; int electrodes_rx; int electrodes_x; int electrodes_y; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ GEN5_PWC_DATA_ELEMENT_SIZE_MASK ; 
 int GEN5_RESP_DATA_STRUCTURE_OFFSET ; 
 scalar_t__ GEN5_RETRIEVE_MUTUAL_PWC_DATA ; 
 scalar_t__ GEN5_RETRIEVE_SELF_CAP_PWC_DATA ; 
 int INT_MAX ; 
 int INT_MIN ; 
 int /*<<< orphan*/  PIP_APP_CMD_REPORT_ID ; 
 int /*<<< orphan*/  PIP_CMD_COMPLETE_SUCCESS (scalar_t__*) ; 
 int PIP_OUTPUT_REPORT_ADDR ; 
 scalar_t__ PIP_RETRIEVE_DATA_STRUCTURE ; 
 int /*<<< orphan*/  VALID_CMD_RESP_HEADER (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  cyapa_gen5_guess_electrodes (struct cyapa*,int*,int*) ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,scalar_t__*,int,scalar_t__*,int*,int,int /*<<< orphan*/ ,int) ; 
 int cyapa_parse_structure_data (scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  cyapa_sort_tsg_pip_app_resp_data ; 
 int get_unaligned_le16 (scalar_t__*) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,scalar_t__*) ; 

__attribute__((used)) static int cyapa_gen5_read_idac_data(struct cyapa *cyapa,
		u8 cmd_code, u8 idac_data_type, int *data_size,
		int *idac_max, int *idac_min, int *idac_ave)
{
	struct pip_app_cmd_head *cmd_head;
	u8 cmd[12];
	u8 resp_data[256];
	int resp_len;
	int read_len;
	int value;
	u16 offset;
	int read_elements;
	bool read_global_idac;
	int sum, count, max_element_cnt;
	int tmp_max, tmp_min, tmp_ave, tmp_sum, tmp_count;
	int electrodes_rx, electrodes_tx;
	int i;
	int error;

	if (cmd_code != PIP_RETRIEVE_DATA_STRUCTURE ||
		(idac_data_type != GEN5_RETRIEVE_MUTUAL_PWC_DATA &&
		idac_data_type != GEN5_RETRIEVE_SELF_CAP_PWC_DATA) ||
		!data_size || !idac_max || !idac_min || !idac_ave)
		return -EINVAL;

	*idac_max = INT_MIN;
	*idac_min = INT_MAX;
	sum = count = tmp_count = 0;
	electrodes_rx = electrodes_tx = 0;
	if (*data_size == 0) {
		/*
		 * Read global idac values firstly.
		 * Currently, no idac data exceed 4 bytes.
		 */
		read_global_idac = true;
		offset = 0;
		*data_size = 4;
		tmp_max = INT_MIN;
		tmp_min = INT_MAX;
		tmp_ave = tmp_sum = tmp_count = 0;

		if (idac_data_type == GEN5_RETRIEVE_MUTUAL_PWC_DATA) {
			if (cyapa->aligned_electrodes_rx == 0) {
				cyapa_gen5_guess_electrodes(cyapa,
					&electrodes_rx, &electrodes_tx);
				cyapa->aligned_electrodes_rx =
					(electrodes_rx + 3) & ~3u;
			}
			max_element_cnt =
				(cyapa->aligned_electrodes_rx + 7) & ~7u;
		} else {
			max_element_cnt = 2;
		}
	} else {
		read_global_idac = false;
		if (*data_size > 4)
			*data_size = 4;
		/* Calculate the start offset in bytes of local PWC data. */
		if (idac_data_type == GEN5_RETRIEVE_MUTUAL_PWC_DATA) {
			offset = cyapa->aligned_electrodes_rx * (*data_size);
			if (cyapa->electrodes_rx == cyapa->electrodes_x)
				electrodes_tx = cyapa->electrodes_y;
			else
				electrodes_tx = cyapa->electrodes_x;
			max_element_cnt = ((cyapa->aligned_electrodes_rx + 7) &
						~7u) * electrodes_tx;
		} else {
			offset = 2;
			max_element_cnt = cyapa->electrodes_x +
						cyapa->electrodes_y;
			max_element_cnt = (max_element_cnt + 3) & ~3u;
		}
	}

	memset(cmd, 0, sizeof(cmd));
	cmd_head = (struct pip_app_cmd_head *)cmd;
	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &cmd_head->addr);
	put_unaligned_le16(sizeof(cmd) - 2, &cmd_head->length);
	cmd_head->report_id = PIP_APP_CMD_REPORT_ID;
	cmd_head->cmd_code = cmd_code;
	do {
		read_elements = (256 - GEN5_RESP_DATA_STRUCTURE_OFFSET) /
				(*data_size);
		read_elements = min(read_elements, max_element_cnt - count);
		read_len = read_elements * (*data_size);

		put_unaligned_le16(offset, &cmd_head->parameter_data[0]);
		put_unaligned_le16(read_len, &cmd_head->parameter_data[2]);
		cmd_head->parameter_data[4] = idac_data_type;
		resp_len = GEN5_RESP_DATA_STRUCTURE_OFFSET + read_len;
		error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
				cmd, sizeof(cmd),
				resp_data, &resp_len,
				500, cyapa_sort_tsg_pip_app_resp_data,
				true);
		if (error || resp_len < GEN5_RESP_DATA_STRUCTURE_OFFSET ||
				!VALID_CMD_RESP_HEADER(resp_data, cmd_code) ||
				!PIP_CMD_COMPLETE_SUCCESS(resp_data) ||
				resp_data[6] != idac_data_type)
			return (error < 0) ? error : -EAGAIN;
		read_len = get_unaligned_le16(&resp_data[7]);
		if (read_len == 0)
			break;

		*data_size = (resp_data[9] & GEN5_PWC_DATA_ELEMENT_SIZE_MASK);
		if (read_len < *data_size)
			return -EINVAL;

		if (read_global_idac &&
			idac_data_type == GEN5_RETRIEVE_SELF_CAP_PWC_DATA) {
			/* Rx's self global idac data. */
			*idac_max = cyapa_parse_structure_data(
				resp_data[9],
				&resp_data[GEN5_RESP_DATA_STRUCTURE_OFFSET],
				*data_size);
			/* Tx's self global idac data. */
			*idac_min = cyapa_parse_structure_data(
				resp_data[9],
				&resp_data[GEN5_RESP_DATA_STRUCTURE_OFFSET +
					   *data_size],
				*data_size);
			break;
		}

		/* Read mutual global idac or local mutual/self PWC data. */
		offset += read_len;
		for (i = 10; i < (read_len + GEN5_RESP_DATA_STRUCTURE_OFFSET);
				i += *data_size) {
			value = cyapa_parse_structure_data(resp_data[9],
					&resp_data[i], *data_size);
			*idac_min = min(value, *idac_min);
			*idac_max = max(value, *idac_max);

			if (idac_data_type == GEN5_RETRIEVE_MUTUAL_PWC_DATA &&
				tmp_count < cyapa->aligned_electrodes_rx &&
				read_global_idac) {
				/*
				 * The value gap between global and local mutual
				 * idac data must bigger than 50%.
				 * Normally, global value bigger than 50,
				 * local values less than 10.
				 */
				if (!tmp_ave || value > tmp_ave / 2) {
					tmp_min = min(value, tmp_min);
					tmp_max = max(value, tmp_max);
					tmp_sum += value;
					tmp_count++;

					tmp_ave = tmp_sum / tmp_count;
				}
			}

			sum += value;
			count++;

			if (count >= max_element_cnt)
				goto out;
		}
	} while (true);

out:
	*idac_ave = count ? (sum / count) : 0;

	if (read_global_idac &&
		idac_data_type == GEN5_RETRIEVE_MUTUAL_PWC_DATA) {
		if (tmp_count == 0)
			return 0;

		if (tmp_count == cyapa->aligned_electrodes_rx) {
			cyapa->electrodes_rx = cyapa->electrodes_rx ?
				cyapa->electrodes_rx : electrodes_rx;
		} else if (tmp_count == electrodes_rx) {
			cyapa->electrodes_rx = cyapa->electrodes_rx ?
				cyapa->electrodes_rx : electrodes_rx;
			cyapa->aligned_electrodes_rx = electrodes_rx;
		} else {
			cyapa->electrodes_rx = cyapa->electrodes_rx ?
				cyapa->electrodes_rx : electrodes_tx;
			cyapa->aligned_electrodes_rx = tmp_count;
		}

		*idac_min = tmp_min;
		*idac_max = tmp_max;
		*idac_ave = tmp_ave;
	}

	return 0;
}