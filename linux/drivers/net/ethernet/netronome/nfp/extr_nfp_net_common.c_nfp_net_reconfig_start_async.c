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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_net {int reconfig_timer_active; int /*<<< orphan*/  reconfig_timer; int /*<<< orphan*/  reconfig_posted; } ;

/* Variables and functions */
 int HZ ; 
 int NFP_NET_POLL_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  nfp_net_reconfig_start (struct nfp_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_reconfig_start_async(struct nfp_net *nn, u32 update)
{
	update |= nn->reconfig_posted;
	nn->reconfig_posted = 0;

	nfp_net_reconfig_start(nn, update);

	nn->reconfig_timer_active = true;
	mod_timer(&nn->reconfig_timer, jiffies + NFP_NET_POLL_TIMEOUT * HZ);
}