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
struct pip_bl_packet_start {int /*<<< orphan*/  data_length; int /*<<< orphan*/  cmd_code; int /*<<< orphan*/  sop; } ;
struct pip_bl_packet_end {int /*<<< orphan*/  eop; int /*<<< orphan*/  crc; } ;
struct pip_bl_initiate_cmd_data {scalar_t__* key; scalar_t__* metadata_raw_parameter; int /*<<< orphan*/  metadata_crc; } ;
struct pip_bl_cmd_head {scalar_t__ data; struct pip_bl_packet_start packet_start; int /*<<< orphan*/  report_id; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct firmware {int dummy; } ;
struct cyapa_tsg_bin_image_data_record {scalar_t__* record_data; } ;
struct cyapa {int dummy; } ;
typedef  int /*<<< orphan*/  resp_data ;

/* Variables and functions */
 int CYAPA_TSG_BL_KEY_SIZE ; 
 int CYAPA_TSG_FLASH_MAP_BLOCK_SIZE ; 
 int CYAPA_TSG_FLASH_MAP_METADATA_SIZE ; 
 int CYAPA_TSG_MAX_CMD_SIZE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  PIP_BL_CMD_INITIATE_BL ; 
 int /*<<< orphan*/  PIP_BL_CMD_REPORT_ID ; 
 int PIP_BL_INITIATE_RESP_LEN ; 
 scalar_t__ PIP_BL_RESP_REPORT_ID ; 
 int /*<<< orphan*/  PIP_CMD_COMPLETE_SUCCESS (scalar_t__*) ; 
 int /*<<< orphan*/  PIP_EOP_KEY ; 
 int PIP_OUTPUT_REPORT_ADDR ; 
 int /*<<< orphan*/  PIP_SOP_KEY ; 
 int crc_itu_t (int,scalar_t__*,int) ; 
 int /*<<< orphan*/  cyapa_empty_pip_output_data (struct cyapa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cyapa_tsg_bin_image_data_record* cyapa_get_image_record_data_num (struct firmware const*,int*) ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,scalar_t__*,int,scalar_t__*,int*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__* cyapa_pip_bl_cmd_key ; 
 int /*<<< orphan*/  cyapa_sort_tsg_pip_bl_resp_data ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int /*<<< orphan*/ *) ; 

int cyapa_pip_bl_initiate(struct cyapa *cyapa, const struct firmware *fw)
{
	struct cyapa_tsg_bin_image_data_record *image_records;
	struct pip_bl_cmd_head *bl_cmd_head;
	struct pip_bl_packet_start *bl_packet_start;
	struct pip_bl_initiate_cmd_data *cmd_data;
	struct pip_bl_packet_end *bl_packet_end;
	u8 cmd[CYAPA_TSG_MAX_CMD_SIZE];
	int cmd_len;
	u16 cmd_data_len;
	u16 cmd_crc = 0;
	u16 meta_data_crc = 0;
	u8 resp_data[11];
	int resp_len;
	int records_num;
	u8 *data;
	int error;

	/* Try to dump all buffered report data before any send command. */
	cyapa_empty_pip_output_data(cyapa, NULL, NULL, NULL);

	memset(cmd, 0, CYAPA_TSG_MAX_CMD_SIZE);
	bl_cmd_head = (struct pip_bl_cmd_head *)cmd;
	cmd_data_len = CYAPA_TSG_BL_KEY_SIZE + CYAPA_TSG_FLASH_MAP_BLOCK_SIZE;
	cmd_len = sizeof(struct pip_bl_cmd_head) + cmd_data_len +
		  sizeof(struct pip_bl_packet_end);

	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &bl_cmd_head->addr);
	put_unaligned_le16(cmd_len - 2, &bl_cmd_head->length);
	bl_cmd_head->report_id = PIP_BL_CMD_REPORT_ID;

	bl_packet_start = &bl_cmd_head->packet_start;
	bl_packet_start->sop = PIP_SOP_KEY;
	bl_packet_start->cmd_code = PIP_BL_CMD_INITIATE_BL;
	/* 8 key bytes and 128 bytes block size */
	put_unaligned_le16(cmd_data_len, &bl_packet_start->data_length);

	cmd_data = (struct pip_bl_initiate_cmd_data *)bl_cmd_head->data;
	memcpy(cmd_data->key, cyapa_pip_bl_cmd_key, CYAPA_TSG_BL_KEY_SIZE);

	image_records = cyapa_get_image_record_data_num(fw, &records_num);

	/* APP_INTEGRITY row is always the last row block */
	data = image_records[records_num - 1].record_data;
	memcpy(cmd_data->metadata_raw_parameter, data,
		CYAPA_TSG_FLASH_MAP_METADATA_SIZE);

	meta_data_crc = crc_itu_t(0xffff, cmd_data->metadata_raw_parameter,
				CYAPA_TSG_FLASH_MAP_METADATA_SIZE);
	put_unaligned_le16(meta_data_crc, &cmd_data->metadata_crc);

	bl_packet_end = (struct pip_bl_packet_end *)(bl_cmd_head->data +
				cmd_data_len);
	cmd_crc = crc_itu_t(0xffff, (u8 *)bl_packet_start,
		sizeof(struct pip_bl_packet_start) + cmd_data_len);
	put_unaligned_le16(cmd_crc, &bl_packet_end->crc);
	bl_packet_end->eop = PIP_EOP_KEY;

	resp_len = sizeof(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, cmd_len,
			resp_data, &resp_len, 12000,
			cyapa_sort_tsg_pip_bl_resp_data, true);
	if (error || resp_len != PIP_BL_INITIATE_RESP_LEN ||
			resp_data[2] != PIP_BL_RESP_REPORT_ID ||
			!PIP_CMD_COMPLETE_SUCCESS(resp_data))
		return error ? error : -EAGAIN;

	return 0;
}