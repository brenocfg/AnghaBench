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
struct nfp_qdisc {int dummy; } ;
struct nfp_abm_link {int /*<<< orphan*/  qdiscs; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_H_MAJ (int /*<<< orphan*/ ) ; 
 struct nfp_qdisc* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfp_qdisc *
nfp_abm_qdisc_find(struct nfp_abm_link *alink, u32 handle)
{
	return radix_tree_lookup(&alink->qdiscs, TC_H_MAJ(handle));
}