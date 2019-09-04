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
typedef  int /*<<< orphan*/  u16 ;
struct si4713_device {int /*<<< orphan*/  tune_rnl; } ;

/* Variables and functions */
 int si4713_tx_tune_status (struct si4713_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si4713_update_tune_status(struct si4713_device *sdev)
{
	int rval;
	u16 f = 0;
	u8 p = 0, a = 0, n = 0;

	rval = si4713_tx_tune_status(sdev, 0x00, &f, &p, &a, &n);

	if (rval < 0)
		goto exit;

/*	TODO: check that power_level and antenna_capacitor really are not
	changed by the hardware. If they are, then these controls should become
	volatiles.
	sdev->power_level = p;
	sdev->antenna_capacitor = a;*/
	sdev->tune_rnl = n;

exit:
	return rval;
}