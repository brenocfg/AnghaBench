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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_abm_link {TYPE_1__* vnic; } ;
struct TYPE_2__ {int max_rx_rings; } ;

/* Variables and functions */
 int nfp_abm_ctrl_set_q_lvl (struct nfp_abm_link*,int,int /*<<< orphan*/ ) ; 

int nfp_abm_ctrl_set_all_q_lvls(struct nfp_abm_link *alink, u32 val)
{
	int i, err;

	for (i = 0; i < alink->vnic->max_rx_rings; i++) {
		err = nfp_abm_ctrl_set_q_lvl(alink, i, val);
		if (err)
			return err;
	}

	return 0;
}