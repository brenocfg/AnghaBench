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
struct bm_mc {scalar_t__ state; struct bm_mc_command* cr; } ;
struct bm_portal {struct bm_mc mc; } ;
struct bm_mc_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  dpaa_zero (struct bm_mc_command*) ; 
 scalar_t__ mc_idle ; 
 scalar_t__ mc_user ; 

__attribute__((used)) static inline struct bm_mc_command *bm_mc_start(struct bm_portal *portal)
{
	struct bm_mc *mc = &portal->mc;

	DPAA_ASSERT(mc->state == mc_idle);
#ifdef CONFIG_FSL_DPAA_CHECKING
	mc->state = mc_user;
#endif
	dpaa_zero(mc->cr);
	return mc->cr;
}