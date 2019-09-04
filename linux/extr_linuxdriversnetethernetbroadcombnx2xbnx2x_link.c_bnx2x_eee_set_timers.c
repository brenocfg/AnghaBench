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
typedef  int u32 ;
struct link_vars {int eee_status; } ;
struct link_params {int port; int eee_mode; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EEE_MODE_ENABLE_LPI ; 
 int EEE_MODE_OUTPUT_TIME ; 
 int EEE_MODE_OVERRIDE_NVRAM ; 
 int EINVAL ; 
 scalar_t__ MISC_REG_CPMU_LP_IDLE_THR_P0 ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int SHMEM_EEE_TIMER_MASK ; 
 int SHMEM_EEE_TIME_OUTPUT_BIT ; 
 int bnx2x_eee_calc_timer (struct link_params*) ; 
 scalar_t__ bnx2x_eee_time_to_nvram (int,int*) ; 

__attribute__((used)) static int bnx2x_eee_set_timers(struct link_params *params,
				   struct link_vars *vars)
{
	u32 eee_idle = 0, eee_mode;
	struct bnx2x *bp = params->bp;

	eee_idle = bnx2x_eee_calc_timer(params);

	if (eee_idle) {
		REG_WR(bp, MISC_REG_CPMU_LP_IDLE_THR_P0 + (params->port << 2),
		       eee_idle);
	} else if ((params->eee_mode & EEE_MODE_ENABLE_LPI) &&
		   (params->eee_mode & EEE_MODE_OVERRIDE_NVRAM) &&
		   (params->eee_mode & EEE_MODE_OUTPUT_TIME)) {
		DP(NETIF_MSG_LINK, "Error: Tx LPI is enabled with timer 0\n");
		return -EINVAL;
	}

	vars->eee_status &= ~(SHMEM_EEE_TIMER_MASK | SHMEM_EEE_TIME_OUTPUT_BIT);
	if (params->eee_mode & EEE_MODE_OUTPUT_TIME) {
		/* eee_idle in 1u --> eee_status in 16u */
		eee_idle >>= 4;
		vars->eee_status |= (eee_idle & SHMEM_EEE_TIMER_MASK) |
				    SHMEM_EEE_TIME_OUTPUT_BIT;
	} else {
		if (bnx2x_eee_time_to_nvram(eee_idle, &eee_mode))
			return -EINVAL;
		vars->eee_status |= eee_mode;
	}

	return 0;
}