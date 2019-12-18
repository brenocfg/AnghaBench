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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum hinic_api_cmd_chain_type { ____Placeholder_hinic_api_cmd_chain_type } hinic_api_cmd_chain_type ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  API_CMD_CELL_ALIGNMENT ; 
 scalar_t__ API_CMD_CELL_DATA_ADDR_SIZE ; 
 scalar_t__ API_CMD_CELL_DESC_SIZE ; 
#define  HINIC_API_CMD_WRITE_TO_MGMT_CPU 128 

__attribute__((used)) static u8 get_cell_data_size(enum hinic_api_cmd_chain_type type)
{
	u8 cell_data_size = 0;

	switch (type) {
	case HINIC_API_CMD_WRITE_TO_MGMT_CPU:
		cell_data_size = ALIGN(API_CMD_CELL_DESC_SIZE +
				       API_CMD_CELL_DATA_ADDR_SIZE,
				       API_CMD_CELL_ALIGNMENT);
		break;
	default:
		break;
	}

	return cell_data_size;
}