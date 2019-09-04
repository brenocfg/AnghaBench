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
struct tc_red_qopt_offload {scalar_t__ parent; scalar_t__ handle; } ;
struct nfp_abm_link {scalar_t__ parent; unsigned int num_qdiscs; TYPE_1__* qdiscs; } ;
struct TYPE_2__ {scalar_t__ handle; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 int TC_H_MIN (scalar_t__) ; 
 scalar_t__ TC_H_ROOT ; 

__attribute__((used)) static int
nfp_abm_red_find(struct nfp_abm_link *alink, struct tc_red_qopt_offload *opt)
{
	unsigned int i = TC_H_MIN(opt->parent) - 1;

	if (opt->parent == TC_H_ROOT)
		i = 0;
	else if (TC_H_MAJ(alink->parent) == TC_H_MAJ(opt->parent))
		i = TC_H_MIN(opt->parent) - 1;
	else
		return -EOPNOTSUPP;

	if (i >= alink->num_qdiscs || opt->handle != alink->qdiscs[i].handle)
		return -EOPNOTSUPP;

	return i;
}