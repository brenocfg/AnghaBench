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
struct nfp_qdisc {int offload_mark; scalar_t__ type; struct nfp_qdisc** children; } ;
struct nfp_abm_link {unsigned int total_queues; } ;

/* Variables and functions */
 scalar_t__ NFP_QDISC_MQ ; 
 int /*<<< orphan*/  nfp_abm_offload_compile_red (struct nfp_abm_link*,struct nfp_qdisc*,unsigned int) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_child_valid (struct nfp_qdisc*,unsigned int) ; 

__attribute__((used)) static void
nfp_abm_offload_compile_mq(struct nfp_abm_link *alink, struct nfp_qdisc *qdisc)
{
	unsigned int i;

	qdisc->offload_mark = qdisc->type == NFP_QDISC_MQ;
	if (!qdisc->offload_mark)
		return;

	for (i = 0; i < alink->total_queues; i++) {
		struct nfp_qdisc *child = qdisc->children[i];

		if (!nfp_abm_qdisc_child_valid(qdisc, i))
			continue;

		nfp_abm_offload_compile_red(alink, child, i);
	}
}