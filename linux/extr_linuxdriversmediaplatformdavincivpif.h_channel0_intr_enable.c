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

/* Variables and functions */
 int /*<<< orphan*/  VPIF_INTEN ; 
 int VPIF_INTEN_FRAME_CH0 ; 
 int /*<<< orphan*/  VPIF_INTEN_SET ; 
 int regr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vpif_lock ; 

__attribute__((used)) static inline void channel0_intr_enable(int enable)
{
	unsigned long flags;

	spin_lock_irqsave(&vpif_lock, flags);

	if (enable) {
		regw((regr(VPIF_INTEN) | 0x10), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | 0x10), VPIF_INTEN_SET);

		regw((regr(VPIF_INTEN) | VPIF_INTEN_FRAME_CH0), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | VPIF_INTEN_FRAME_CH0),
							VPIF_INTEN_SET);
	} else {
		regw((regr(VPIF_INTEN) & (~VPIF_INTEN_FRAME_CH0)), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | VPIF_INTEN_FRAME_CH0),
							VPIF_INTEN_SET);
	}
	spin_unlock_irqrestore(&vpif_lock, flags);
}