#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mxl {TYPE_1__* base; int /*<<< orphan*/  i2cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  HYDRA_FIRMWARE_VERSION ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int read_by_mnemonic (struct mxl*,int,int,int,int /*<<< orphan*/ *) ; 
 int read_register (struct mxl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_fwinfo(struct mxl *state)
{
	int status;
	u32 val = 0;

	status = read_by_mnemonic(state, 0x90000190, 0, 3, &val);
	if (status)
		return status;
	dev_info(state->i2cdev, "chipID=%08x\n", val);

	status = read_by_mnemonic(state, 0x80030004, 8, 8, &val);
	if (status)
		return status;
	dev_info(state->i2cdev, "chipVer=%08x\n", val);

	status = read_register(state, HYDRA_FIRMWARE_VERSION, &val);
	if (status)
		return status;
	dev_info(state->i2cdev, "FWVer=%08x\n", val);

	state->base->fwversion = val;
	return status;
}