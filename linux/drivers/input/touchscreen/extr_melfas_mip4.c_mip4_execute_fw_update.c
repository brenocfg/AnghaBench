#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mip4_ts {TYPE_2__* client; TYPE_1__* input; } ;
struct mip4_bin_tail {int dummy; } ;
struct firmware {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ users; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int mip4_flash_fw (struct mip4_ts*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mip4_parse_firmware (struct mip4_ts*,struct firmware const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mip4_bin_tail const**) ; 
 int /*<<< orphan*/  mip4_power_off (struct mip4_ts*) ; 
 int mip4_power_on (struct mip4_ts*) ; 

__attribute__((used)) static int mip4_execute_fw_update(struct mip4_ts *ts, const struct firmware *fw)
{
	const struct mip4_bin_tail *fw_info;
	u32 fw_start_offset;
	u32 fw_size;
	int retires = 3;
	int error;

	error = mip4_parse_firmware(ts, fw,
				    &fw_start_offset, &fw_size, &fw_info);
	if (error)
		return error;

	if (ts->input->users) {
		disable_irq(ts->client->irq);
	} else {
		error = mip4_power_on(ts);
		if (error)
			return error;
	}

	/* Update firmware */
	do {
		error = mip4_flash_fw(ts, fw->data, fw_size, fw_start_offset);
		if (!error)
			break;
	} while (--retires);

	if (error)
		dev_err(&ts->client->dev,
			"Failed to flash firmware: %d\n", error);

	/* Enable IRQ */
	if (ts->input->users)
		enable_irq(ts->client->irq);
	else
		mip4_power_off(ts);

	return error ? error : 0;
}