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
typedef  int u32 ;
struct TYPE_2__ {int pixelformat; } ;
struct rvin_dev {unsigned int alpha; scalar_t__ state; int /*<<< orphan*/  qlock; TYPE_1__ format; } ;

/* Variables and functions */
 scalar_t__ STOPPED ; 
#define  V4L2_PIX_FMT_ABGR32 129 
#define  V4L2_PIX_FMT_ARGB555 128 
 int VNDMR_A8BIT (int) ; 
 int VNDMR_A8BIT_MASK ; 
 int VNDMR_ABIT ; 
 int /*<<< orphan*/  VNDMR_REG ; 
 int rvin_read (struct rvin_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvin_write (struct rvin_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rvin_set_alpha(struct rvin_dev *vin, unsigned int alpha)
{
	unsigned long flags;
	u32 dmr;

	spin_lock_irqsave(&vin->qlock, flags);

	vin->alpha = alpha;

	if (vin->state == STOPPED)
		goto out;

	switch (vin->format.pixelformat) {
	case V4L2_PIX_FMT_ARGB555:
		dmr = rvin_read(vin, VNDMR_REG) & ~VNDMR_ABIT;
		if (vin->alpha)
			dmr |= VNDMR_ABIT;
		break;
	case V4L2_PIX_FMT_ABGR32:
		dmr = rvin_read(vin, VNDMR_REG) & ~VNDMR_A8BIT_MASK;
		dmr |= VNDMR_A8BIT(vin->alpha);
		break;
	default:
		goto out;
	}

	rvin_write(vin, dmr,  VNDMR_REG);
out:
	spin_unlock_irqrestore(&vin->qlock, flags);
}