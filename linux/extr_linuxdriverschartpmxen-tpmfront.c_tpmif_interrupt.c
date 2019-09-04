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
struct tpm_private {int /*<<< orphan*/  read_queue; TYPE_1__* shr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  VTPM_STATE_CANCEL 131 
#define  VTPM_STATE_FINISH 130 
#define  VTPM_STATE_IDLE 129 
#define  VTPM_STATE_SUBMIT 128 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t tpmif_interrupt(int dummy, void *dev_id)
{
	struct tpm_private *priv = dev_id;

	switch (priv->shr->state) {
	case VTPM_STATE_IDLE:
	case VTPM_STATE_FINISH:
		wake_up_interruptible(&priv->read_queue);
		break;
	case VTPM_STATE_SUBMIT:
	case VTPM_STATE_CANCEL:
	default:
		break;
	}
	return IRQ_HANDLED;
}