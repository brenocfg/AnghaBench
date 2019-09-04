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
struct em28xx_IR {struct em28xx_IR* i2c_client; int /*<<< orphan*/  rc; } ;
struct em28xx {int /*<<< orphan*/  ref; struct em28xx_IR* ir; TYPE_1__* intf; scalar_t__ is_audio_only; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  em28xx_free_device ; 
 int /*<<< orphan*/  em28xx_shutdown_buttons (struct em28xx*) ; 
 int /*<<< orphan*/  kfree (struct em28xx_IR*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em28xx_ir_fini(struct em28xx *dev)
{
	struct em28xx_IR *ir = dev->ir;

	if (dev->is_audio_only) {
		/* Shouldn't initialize IR for this interface */
		return 0;
	}

	dev_info(&dev->intf->dev, "Closing input extension\n");

	em28xx_shutdown_buttons(dev);

	/* skip detach on non attached boards */
	if (!ir)
		goto ref_put;

	rc_unregister_device(ir->rc);

	kfree(ir->i2c_client);

	/* done */
	kfree(ir);
	dev->ir = NULL;

ref_put:
	kref_put(&dev->ref, em28xx_free_device);

	return 0;
}