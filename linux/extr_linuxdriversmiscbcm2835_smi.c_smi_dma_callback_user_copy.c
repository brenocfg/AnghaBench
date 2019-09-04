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
struct TYPE_2__ {int /*<<< orphan*/  callback_sem; } ;
struct bcm2835_smi_instance {TYPE_1__ bounce; } ;

/* Variables and functions */
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smi_dma_callback_user_copy(void *param)
{
	/* Notify the bottom half that a chunk is ready for user copy */
	struct bcm2835_smi_instance *inst =
		(struct bcm2835_smi_instance *)param;

	up(&inst->bounce.callback_sem);
}