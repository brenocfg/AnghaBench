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
struct nfp_qdisc {TYPE_1__** children; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_cnt; } ;

/* Variables and functions */
 scalar_t__ nfp_abm_qdisc_child_valid (struct nfp_qdisc*,unsigned int) ; 

__attribute__((used)) static void
nfp_abm_qdisc_unlink_children(struct nfp_qdisc *qdisc,
			      unsigned int start, unsigned int end)
{
	unsigned int i;

	for (i = start; i < end; i++)
		if (nfp_abm_qdisc_child_valid(qdisc, i)) {
			qdisc->children[i]->use_cnt--;
			qdisc->children[i] = NULL;
		}
}