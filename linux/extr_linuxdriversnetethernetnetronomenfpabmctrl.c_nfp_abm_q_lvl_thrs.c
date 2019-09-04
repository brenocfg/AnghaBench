#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfp_abm_link {unsigned int queue_base; TYPE_2__* abm; } ;
struct TYPE_4__ {TYPE_1__* q_lvls; } ;
struct TYPE_3__ {unsigned long long addr; } ;

/* Variables and functions */
 unsigned int NFP_QLVL_STRIDE ; 
 unsigned long long NFP_QLVL_THRS ; 

__attribute__((used)) static unsigned long long
nfp_abm_q_lvl_thrs(struct nfp_abm_link *alink, unsigned int queue)
{
	return alink->abm->q_lvls->addr +
		(alink->queue_base + queue) * NFP_QLVL_STRIDE + NFP_QLVL_THRS;
}