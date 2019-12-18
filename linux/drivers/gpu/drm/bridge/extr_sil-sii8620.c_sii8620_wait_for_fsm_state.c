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
typedef  int u8 ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int BIT_COC_STAT_0_PLL_LOCKED ; 
 int EBUSY ; 
 int ETIMEDOUT ; 
 int MSK_COC_STAT_0_FSM_STATE ; 
 int /*<<< orphan*/  REG_COC_STAT_0 ; 
 int sii8620_readb (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sii8620_wait_for_fsm_state(struct sii8620 *ctx, u8 state)
{
	int i;

	for (i = 0; i < 10; ++i) {
		u8 s = sii8620_readb(ctx, REG_COC_STAT_0);

		if ((s & MSK_COC_STAT_0_FSM_STATE) == state)
			return 0;
		if (!(s & BIT_COC_STAT_0_PLL_LOCKED))
			return -EBUSY;
		usleep_range(4000, 6000);
	}
	return -ETIMEDOUT;
}