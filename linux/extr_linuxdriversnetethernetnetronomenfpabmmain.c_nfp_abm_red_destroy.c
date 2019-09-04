#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nfp_abm_link {unsigned int num_qdiscs; scalar_t__ parent; TYPE_1__* qdiscs; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ handle; } ;

/* Variables and functions */
 scalar_t__ TC_H_ROOT ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfp_abm_ctrl_set_q_lvl (struct nfp_abm_link*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_reset_root (struct net_device*,struct nfp_abm_link*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_abm_red_destroy(struct net_device *netdev, struct nfp_abm_link *alink,
		    u32 handle)
{
	unsigned int i;

	for (i = 0; i < alink->num_qdiscs; i++)
		if (handle == alink->qdiscs[i].handle)
			break;
	if (i == alink->num_qdiscs)
		return;

	if (alink->parent == TC_H_ROOT) {
		nfp_abm_reset_root(netdev, alink, TC_H_ROOT, 0);
	} else {
		nfp_abm_ctrl_set_q_lvl(alink, i, ~0);
		memset(&alink->qdiscs[i], 0, sizeof(*alink->qdiscs));
	}
}