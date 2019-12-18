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
struct TYPE_2__ {scalar_t__ workq; } ;
struct gm12u320_device {int /*<<< orphan*/  cmd_buf; int /*<<< orphan*/ * data_buf; TYPE_1__ fb_update; } ;

/* Variables and functions */
 int GM12U320_BLOCK_COUNT ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gm12u320_usb_free(struct gm12u320_device *gm12u320)
{
	int i;

	if (gm12u320->fb_update.workq)
		destroy_workqueue(gm12u320->fb_update.workq);

	for (i = 0; i < GM12U320_BLOCK_COUNT; i++)
		kfree(gm12u320->data_buf[i]);

	kfree(gm12u320->cmd_buf);
}