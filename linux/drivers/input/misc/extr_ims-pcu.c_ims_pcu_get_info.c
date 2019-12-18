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
struct ims_pcu {int /*<<< orphan*/ * cmd_buf; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  date_of_manufacturing; int /*<<< orphan*/  part_number; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_INFO ; 
 size_t IMS_PCU_INFO_DOM_OFFSET ; 
 size_t IMS_PCU_INFO_PART_OFFSET ; 
 size_t IMS_PCU_INFO_SERIAL_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ims_pcu_execute_query (struct ims_pcu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ims_pcu_get_info(struct ims_pcu *pcu)
{
	int error;

	error = ims_pcu_execute_query(pcu, GET_INFO);
	if (error) {
		dev_err(pcu->dev,
			"GET_INFO command failed, error: %d\n", error);
		return error;
	}

	memcpy(pcu->part_number,
	       &pcu->cmd_buf[IMS_PCU_INFO_PART_OFFSET],
	       sizeof(pcu->part_number));
	memcpy(pcu->date_of_manufacturing,
	       &pcu->cmd_buf[IMS_PCU_INFO_DOM_OFFSET],
	       sizeof(pcu->date_of_manufacturing));
	memcpy(pcu->serial_number,
	       &pcu->cmd_buf[IMS_PCU_INFO_SERIAL_OFFSET],
	       sizeof(pcu->serial_number));

	return 0;
}