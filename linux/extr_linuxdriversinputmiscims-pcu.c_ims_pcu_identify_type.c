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
struct ims_pcu {int /*<<< orphan*/  dev; int /*<<< orphan*/ * cmd_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_DEVICE_ID ; 
 size_t IMS_PCU_DATA_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ims_pcu_execute_query (struct ims_pcu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ims_pcu_identify_type(struct ims_pcu *pcu, u8 *device_id)
{
	int error;

	error = ims_pcu_execute_query(pcu, GET_DEVICE_ID);
	if (error) {
		dev_err(pcu->dev,
			"GET_DEVICE_ID command failed, error: %d\n", error);
		return error;
	}

	*device_id = pcu->cmd_buf[IMS_PCU_DATA_OFFSET];
	dev_dbg(pcu->dev, "Detected device ID: %d\n", *device_id);

	return 0;
}