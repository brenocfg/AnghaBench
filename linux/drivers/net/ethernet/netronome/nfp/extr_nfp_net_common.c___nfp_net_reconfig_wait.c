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
struct nfp_net {int dummy; } ;

/* Variables and functions */
 scalar_t__ nfp_net_reconfig_check_done (struct nfp_net*,int) ; 
 int time_is_before_eq_jiffies (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static bool __nfp_net_reconfig_wait(struct nfp_net *nn, unsigned long deadline)
{
	bool timed_out = false;
	int i;

	/* Poll update field, waiting for NFP to ack the config.
	 * Do an opportunistic wait-busy loop, afterward sleep.
	 */
	for (i = 0; i < 50; i++) {
		if (nfp_net_reconfig_check_done(nn, false))
			return false;
		udelay(4);
	}

	while (!nfp_net_reconfig_check_done(nn, timed_out)) {
		usleep_range(250, 500);
		timed_out = time_is_before_eq_jiffies(deadline);
	}

	return timed_out;
}