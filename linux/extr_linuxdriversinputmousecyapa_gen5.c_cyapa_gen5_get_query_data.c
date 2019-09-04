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
typedef  int u8 ;
typedef  int u16 ;
struct cyapa {int platform_ver; scalar_t__ gen; int fw_maj_ver; int fw_min_ver; int electrodes_x; int electrodes_y; int physical_size_x; int physical_size_y; int max_abs_x; int max_abs_y; int max_z; int x_origin; int y_origin; int btn_capability; char* product_id; } ;
typedef  int /*<<< orphan*/  resp_data ;

/* Variables and functions */
 int CAPABILITY_BTN_MASK ; 
 scalar_t__ CYAPA_GEN5 ; 
 int EINVAL ; 
 int EIO ; 
 int PIP_BL_PLATFORM_VER_MASK ; 
 int PIP_BL_PLATFORM_VER_SHIFT ; 
 int PIP_PRODUCT_FAMILY_MASK ; 
 int PIP_PRODUCT_FAMILY_TRACKPAD ; 
 int /*<<< orphan*/  PIP_READ_SYS_INFO_CMD_LENGTH ; 
 int PIP_READ_SYS_INFO_RESP_LENGTH ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cyapa_pip_sort_system_info_data ; 
 int get_unaligned_le16 (int*) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 int /*<<< orphan*/  pip_read_sys_info ; 

__attribute__((used)) static int cyapa_gen5_get_query_data(struct cyapa *cyapa)
{
	u8 resp_data[PIP_READ_SYS_INFO_RESP_LENGTH];
	int resp_len;
	u16 product_family;
	int error;

	resp_len = sizeof(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			pip_read_sys_info, PIP_READ_SYS_INFO_CMD_LENGTH,
			resp_data, &resp_len,
			2000, cyapa_pip_sort_system_info_data, false);
	if (error || resp_len < sizeof(resp_data))
		return error ? error : -EIO;

	product_family = get_unaligned_le16(&resp_data[7]);
	if ((product_family & PIP_PRODUCT_FAMILY_MASK) !=
		PIP_PRODUCT_FAMILY_TRACKPAD)
		return -EINVAL;

	cyapa->platform_ver = (resp_data[49] >> PIP_BL_PLATFORM_VER_SHIFT) &
			      PIP_BL_PLATFORM_VER_MASK;
	if (cyapa->gen == CYAPA_GEN5 && cyapa->platform_ver < 2) {
		/* Gen5 firmware that does not support proximity. */
		cyapa->fw_maj_ver = resp_data[15];
		cyapa->fw_min_ver = resp_data[16];
	} else {
		cyapa->fw_maj_ver = resp_data[9];
		cyapa->fw_min_ver = resp_data[10];
	}

	cyapa->electrodes_x = resp_data[52];
	cyapa->electrodes_y = resp_data[53];

	cyapa->physical_size_x =  get_unaligned_le16(&resp_data[54]) / 100;
	cyapa->physical_size_y = get_unaligned_le16(&resp_data[56]) / 100;

	cyapa->max_abs_x = get_unaligned_le16(&resp_data[58]);
	cyapa->max_abs_y = get_unaligned_le16(&resp_data[60]);

	cyapa->max_z = get_unaligned_le16(&resp_data[62]);

	cyapa->x_origin = resp_data[64] & 0x01;
	cyapa->y_origin = resp_data[65] & 0x01;

	cyapa->btn_capability = (resp_data[70] << 3) & CAPABILITY_BTN_MASK;

	memcpy(&cyapa->product_id[0], &resp_data[33], 5);
	cyapa->product_id[5] = '-';
	memcpy(&cyapa->product_id[6], &resp_data[38], 6);
	cyapa->product_id[12] = '-';
	memcpy(&cyapa->product_id[13], &resp_data[44], 2);
	cyapa->product_id[15] = '\0';

	if (!cyapa->electrodes_x || !cyapa->electrodes_y ||
		!cyapa->physical_size_x || !cyapa->physical_size_y ||
		!cyapa->max_abs_x || !cyapa->max_abs_y || !cyapa->max_z)
		return -EINVAL;

	return 0;
}