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
struct rvin_dev {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int HW_BUFFER_NUM ; 
 int /*<<< orphan*/  STARTING ; 
 int /*<<< orphan*/  VNFC_C_FRAME ; 
 int /*<<< orphan*/  VNFC_REG ; 
 int /*<<< orphan*/  rvin_crop_scale_comp (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_fill_hw_slot (struct rvin_dev*,int) ; 
 int rvin_setup (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_write (struct rvin_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vin_dbg (struct rvin_dev*,char*) ; 

__attribute__((used)) static int rvin_capture_start(struct rvin_dev *vin)
{
	int slot, ret;

	for (slot = 0; slot < HW_BUFFER_NUM; slot++)
		rvin_fill_hw_slot(vin, slot);

	rvin_crop_scale_comp(vin);

	ret = rvin_setup(vin);
	if (ret)
		return ret;

	vin_dbg(vin, "Starting to capture\n");

	/* Continuous Frame Capture Mode */
	rvin_write(vin, VNFC_C_FRAME, VNFC_REG);

	vin->state = STARTING;

	return 0;
}