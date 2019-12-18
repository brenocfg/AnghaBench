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
struct nfp_abm_link {unsigned int queue_base; int /*<<< orphan*/  abm; } ;

/* Variables and functions */
 unsigned int NFP_NET_MAX_RX_RINGS ; 
 int __nfp_abm_ctrl_set_q_lvl (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

int nfp_abm_ctrl_set_q_lvl(struct nfp_abm_link *alink, unsigned int band,
			   unsigned int queue, u32 val)
{
	unsigned int threshold;

	threshold = band * NFP_NET_MAX_RX_RINGS + alink->queue_base + queue;

	return __nfp_abm_ctrl_set_q_lvl(alink->abm, threshold, val);
}