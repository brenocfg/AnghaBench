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
struct bm_mc {scalar_t__ state; } ;
struct bm_portal {struct bm_mc mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 scalar_t__ mc_idle ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static void bm_mc_finish(struct bm_portal *portal)
{
#ifdef CONFIG_FSL_DPAA_CHECKING
	struct bm_mc *mc = &portal->mc;

	DPAA_ASSERT(mc->state == mc_idle);
	if (mc->state != mc_idle)
		pr_crit("Losing incomplete MC command\n");
#endif
}