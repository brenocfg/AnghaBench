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
struct nfp_qdisc {unsigned int num_children; struct nfp_qdisc** children; int /*<<< orphan*/  use_cnt; } ;
struct nfp_abm_link {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nfp_qdisc* NFP_QDISC_UNTRACKED ; 
 scalar_t__ WARN (int,char*,unsigned int,unsigned int) ; 
 struct nfp_qdisc* nfp_abm_qdisc_find (struct nfp_abm_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_offload_update (struct nfp_abm_link*) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_unlink_children (struct nfp_qdisc*,unsigned int,unsigned int) ; 

__attribute__((used)) static int
nfp_abm_qdisc_graft(struct nfp_abm_link *alink, u32 handle, u32 child_handle,
		    unsigned int id)
{
	struct nfp_qdisc *parent, *child;

	parent = nfp_abm_qdisc_find(alink, handle);
	if (!parent)
		return 0;

	if (WARN(id >= parent->num_children,
		 "graft child out of bound %d >= %d\n",
		 id, parent->num_children))
		return -EINVAL;

	nfp_abm_qdisc_unlink_children(parent, id, id + 1);

	child = nfp_abm_qdisc_find(alink, child_handle);
	if (child)
		child->use_cnt++;
	else
		child = NFP_QDISC_UNTRACKED;
	parent->children[id] = child;

	nfp_abm_qdisc_offload_update(alink);

	return 0;
}