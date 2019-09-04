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
typedef  int /*<<< orphan*/  u_long ;
struct IsdnCardState {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  CARD_INIT 131 
#define  CARD_RELEASE 130 
#define  CARD_RESET 129 
#define  CARD_TEST 128 
 int /*<<< orphan*/  niccy_reset (struct IsdnCardState*) ; 
 int /*<<< orphan*/  release_io_niccy (struct IsdnCardState*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niccy_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;

	switch (mt) {
	case CARD_RESET:
		spin_lock_irqsave(&cs->lock, flags);
		niccy_reset(cs);
		spin_unlock_irqrestore(&cs->lock, flags);
		return 0;
	case CARD_RELEASE:
		release_io_niccy(cs);
		return 0;
	case CARD_INIT:
		spin_lock_irqsave(&cs->lock, flags);
		niccy_reset(cs);
		spin_unlock_irqrestore(&cs->lock, flags);
		return 0;
	case CARD_TEST:
		return 0;
	}
	return 0;
}