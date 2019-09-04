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
typedef  int u8 ;
struct tpm_private {TYPE_1__* shr; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
#define  VTPM_STATE_CANCEL 131 
#define  VTPM_STATE_FINISH 130 
#define  VTPM_STATE_IDLE 129 
#define  VTPM_STATE_SUBMIT 128 
 int VTPM_STATUS_CANCELED ; 
 int VTPM_STATUS_IDLE ; 
 int VTPM_STATUS_RESULT ; 
 int VTPM_STATUS_RUNNING ; 
 struct tpm_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 vtpm_status(struct tpm_chip *chip)
{
	struct tpm_private *priv = dev_get_drvdata(&chip->dev);
	switch (priv->shr->state) {
	case VTPM_STATE_IDLE:
		return VTPM_STATUS_IDLE | VTPM_STATUS_CANCELED;
	case VTPM_STATE_FINISH:
		return VTPM_STATUS_IDLE | VTPM_STATUS_RESULT;
	case VTPM_STATE_SUBMIT:
	case VTPM_STATE_CANCEL: /* cancel requested, not yet canceled */
		return VTPM_STATUS_RUNNING;
	default:
		return 0;
	}
}