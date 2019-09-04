#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct timer_group_priv {TYPE_2__* regs; int /*<<< orphan*/  group_tcr; TYPE_1__* timer; } ;
struct cascade_priv {int tcr_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  gtbcr; int /*<<< orphan*/  gtccr; } ;
struct TYPE_3__ {struct cascade_priv* cascade_handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_TICKS_CASCADE ; 
 int MPIC_TIMER_TCR_ROVR_OFFSET ; 
 int TIMER_STOP ; 
 int div_u64_rem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setbits32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_cascade_timer(struct timer_group_priv *priv, u64 ticks,
		unsigned int num)
{
	struct cascade_priv *casc_priv;
	u32 tcr;
	u32 tmp_ticks;
	u32 rem_ticks;

	/* set group tcr reg for cascade */
	casc_priv = priv->timer[num].cascade_handle;
	if (!casc_priv)
		return -EINVAL;

	tcr = casc_priv->tcr_value |
		(casc_priv->tcr_value << MPIC_TIMER_TCR_ROVR_OFFSET);
	setbits32(priv->group_tcr, tcr);

	tmp_ticks = div_u64_rem(ticks, MAX_TICKS_CASCADE, &rem_ticks);

	out_be32(&priv->regs[num].gtccr, 0);
	out_be32(&priv->regs[num].gtbcr, tmp_ticks | TIMER_STOP);

	out_be32(&priv->regs[num - 1].gtccr, 0);
	out_be32(&priv->regs[num - 1].gtbcr, rem_ticks);

	return 0;
}