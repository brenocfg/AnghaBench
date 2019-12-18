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
typedef  union qm_mc_command {int dummy; } qm_mc_command ;
struct qm_mc {scalar_t__ state; union qm_mc_command* cr; } ;
struct qm_portal {struct qm_mc mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  dpaa_zero (union qm_mc_command*) ; 
 scalar_t__ qman_mc_idle ; 
 scalar_t__ qman_mc_user ; 

__attribute__((used)) static inline union qm_mc_command *qm_mc_start(struct qm_portal *portal)
{
	struct qm_mc *mc = &portal->mc;

	DPAA_ASSERT(mc->state == qman_mc_idle);
#ifdef CONFIG_FSL_DPAA_CHECKING
	mc->state = qman_mc_user;
#endif
	dpaa_zero(mc->cr);
	return mc->cr;
}