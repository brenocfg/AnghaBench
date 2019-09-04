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
struct cyapa {scalar_t__ state; char* product_id; int fw_maj_ver; int fw_min_ver; int btn_capability; int gen; int max_abs_x; int max_abs_y; int physical_size_x; int physical_size_y; int max_z; } ;

/* Variables and functions */
 int CAPABILITY_BTN_MASK ; 
 int /*<<< orphan*/  CYAPA_CMD_GROUP_QUERY ; 
 scalar_t__ CYAPA_STATE_OP ; 
 int EBUSY ; 
 int EIO ; 
 int QUERY_DATA_SIZE ; 
 int cyapa_read_block (struct cyapa*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 

__attribute__((used)) static int cyapa_gen3_get_query_data(struct cyapa *cyapa)
{
	u8 query_data[QUERY_DATA_SIZE];
	int ret;

	if (cyapa->state != CYAPA_STATE_OP)
		return -EBUSY;

	ret = cyapa_read_block(cyapa, CYAPA_CMD_GROUP_QUERY, query_data);
	if (ret != QUERY_DATA_SIZE)
		return (ret < 0) ? ret : -EIO;

	memcpy(&cyapa->product_id[0], &query_data[0], 5);
	cyapa->product_id[5] = '-';
	memcpy(&cyapa->product_id[6], &query_data[5], 6);
	cyapa->product_id[12] = '-';
	memcpy(&cyapa->product_id[13], &query_data[11], 2);
	cyapa->product_id[15] = '\0';

	cyapa->fw_maj_ver = query_data[15];
	cyapa->fw_min_ver = query_data[16];

	cyapa->btn_capability = query_data[19] & CAPABILITY_BTN_MASK;

	cyapa->gen = query_data[20] & 0x0f;

	cyapa->max_abs_x = ((query_data[21] & 0xf0) << 4) | query_data[22];
	cyapa->max_abs_y = ((query_data[21] & 0x0f) << 8) | query_data[23];

	cyapa->physical_size_x =
		((query_data[24] & 0xf0) << 4) | query_data[25];
	cyapa->physical_size_y =
		((query_data[24] & 0x0f) << 8) | query_data[26];

	cyapa->max_z = 255;

	return 0;
}