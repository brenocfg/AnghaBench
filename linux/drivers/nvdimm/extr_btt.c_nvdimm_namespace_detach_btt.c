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
struct nd_btt {struct btt* btt; } ;
struct btt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btt_fini (struct btt*) ; 

int nvdimm_namespace_detach_btt(struct nd_btt *nd_btt)
{
	struct btt *btt = nd_btt->btt;

	btt_fini(btt);
	nd_btt->btt = NULL;

	return 0;
}