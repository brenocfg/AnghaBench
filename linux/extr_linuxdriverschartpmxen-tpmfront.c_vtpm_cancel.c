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
struct tpm_private {int /*<<< orphan*/  evtchn; TYPE_1__* shr; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTPM_STATE_CANCEL ; 
 struct tpm_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void vtpm_cancel(struct tpm_chip *chip)
{
	struct tpm_private *priv = dev_get_drvdata(&chip->dev);
	priv->shr->state = VTPM_STATE_CANCEL;
	wmb();
	notify_remote_via_evtchn(priv->evtchn);
}