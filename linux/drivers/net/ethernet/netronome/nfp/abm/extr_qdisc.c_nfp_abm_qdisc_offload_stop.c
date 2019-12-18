#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int num_bands; TYPE_2__* band; } ;
struct nfp_qdisc {TYPE_3__ red; int /*<<< orphan*/  handle; scalar_t__ use_cnt; } ;
struct nfp_abm_link {TYPE_5__* abm; } ;
struct TYPE_10__ {TYPE_4__* app; } ;
struct TYPE_9__ {int /*<<< orphan*/  cpp; } ;
struct TYPE_6__ {scalar_t__ backlog_bytes; scalar_t__ backlog_pkts; } ;
struct TYPE_7__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_abm_qdisc_is_red (struct nfp_qdisc*) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_abm_qdisc_offload_stop(struct nfp_abm_link *alink, struct nfp_qdisc *qdisc)
{
	unsigned int i;

	/* Don't complain when qdisc is getting unlinked */
	if (qdisc->use_cnt)
		nfp_warn(alink->abm->app->cpp, "Offload of '%08x' stopped\n",
			 qdisc->handle);

	if (!nfp_abm_qdisc_is_red(qdisc))
		return;

	for (i = 0; i < qdisc->red.num_bands; i++) {
		qdisc->red.band[i].stats.backlog_pkts = 0;
		qdisc->red.band[i].stats.backlog_bytes = 0;
	}
}