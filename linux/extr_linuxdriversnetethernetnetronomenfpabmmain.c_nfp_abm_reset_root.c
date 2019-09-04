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
struct nfp_abm_link {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nfp_abm_reset_root (struct net_device*,struct nfp_abm_link*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_abm_reset_root(struct net_device *netdev, struct nfp_abm_link *alink,
		   u32 handle, unsigned int qs)
{
	__nfp_abm_reset_root(netdev, alink, handle, qs, ~0);
}