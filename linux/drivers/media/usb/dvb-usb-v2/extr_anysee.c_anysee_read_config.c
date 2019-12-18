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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_usb_device {TYPE_1__* udev; } ;
struct anysee_state {int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int anysee_get_hw_info (struct dvb_usb_device*,int /*<<< orphan*/ *) ; 
 struct anysee_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int anysee_read_config(struct dvb_usb_device *d)
{
	struct anysee_state *state = d_to_priv(d);
	int ret;
	u8 hw_info[3];

	/*
	 * Check which hardware we have.
	 * We must do this call two times to get reliable values (hw/fw bug).
	 */
	ret = anysee_get_hw_info(d, hw_info);
	if (ret)
		goto error;

	ret = anysee_get_hw_info(d, hw_info);
	if (ret)
		goto error;

	/*
	 * Meaning of these info bytes are guessed.
	 */
	dev_info(&d->udev->dev, "%s: firmware version %d.%d hardware id %d\n",
			KBUILD_MODNAME, hw_info[1], hw_info[2], hw_info[0]);

	state->hw = hw_info[0];
error:
	return ret;
}