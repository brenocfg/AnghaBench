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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 unsigned int HPET_TN_ENABLE ; 
 int /*<<< orphan*/  HPET_Tn_CFG (int) ; 
 unsigned int hpet_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpet_shutdown(struct clock_event_device *evt, int timer)
{
	unsigned int cfg;

	cfg = hpet_readl(HPET_Tn_CFG(timer));
	cfg &= ~HPET_TN_ENABLE;
	hpet_writel(cfg, HPET_Tn_CFG(timer));

	return 0;
}