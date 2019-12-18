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
struct TYPE_3__ {unsigned int num_bands; TYPE_2__* band; } ;
struct nfp_qdisc {TYPE_1__ red; } ;
struct nfp_abm_link {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  prev_xstats; int /*<<< orphan*/  prev_stats; } ;

/* Variables and functions */
 int __nfp_abm_stats_init (struct nfp_abm_link*,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfp_abm_stats_init(struct nfp_abm_link *alink, struct nfp_qdisc *qdisc,
		   unsigned int queue)
{
	unsigned int i;
	int err;

	for (i = 0; i < qdisc->red.num_bands; i++) {
		err = __nfp_abm_stats_init(alink, i, queue,
					   &qdisc->red.band[i].prev_stats,
					   &qdisc->red.band[i].prev_xstats);
		if (err)
			return err;
	}

	return 0;
}