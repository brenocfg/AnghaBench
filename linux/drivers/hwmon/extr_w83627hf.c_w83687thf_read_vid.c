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
struct w83627hf_sio_data {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  W83627HF_LD_HWM ; 
 int /*<<< orphan*/  W83687THF_VID_CFG ; 
 int /*<<< orphan*/  W83687THF_VID_DATA ; 
 int /*<<< orphan*/  W83687THF_VID_EN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct w83627hf_sio_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ superio_enter (struct w83627hf_sio_data*) ; 
 int /*<<< orphan*/  superio_exit (struct w83627hf_sio_data*) ; 
 int superio_inb (struct w83627hf_sio_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_select (struct w83627hf_sio_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w83687thf_read_vid(struct platform_device *pdev)
{
	struct w83627hf_sio_data *sio_data = dev_get_platdata(&pdev->dev);
	int res = 0xff;

	if (superio_enter(sio_data)) {
		/*
		 * Some other driver reserved the address space for itself.
		 * We don't want to fail driver instantiation because of that,
		 * so display a warning and keep going.
		 */
		dev_warn(&pdev->dev,
			 "Can not read VID data: Failed to enable SuperIO access\n");
		return res;
	}

	superio_select(sio_data, W83627HF_LD_HWM);

	/* Make sure these GPIO pins are enabled */
	if (!(superio_inb(sio_data, W83687THF_VID_EN) & (1 << 2))) {
		dev_dbg(&pdev->dev, "VID disabled, no VID function\n");
		goto exit;
	}

	/* Make sure the pins are configured for input */
	if (!(superio_inb(sio_data, W83687THF_VID_CFG) & (1 << 4))) {
		dev_dbg(&pdev->dev, "VID configured as output, "
			"no VID function\n");
		goto exit;
	}

	res = superio_inb(sio_data, W83687THF_VID_DATA) & 0x3f;

exit:
	superio_exit(sio_data);
	return res;
}