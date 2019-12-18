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
struct usnic_vnic_res_chunk {int type; } ;
struct usnic_ib_qp_grp {struct usnic_vnic_res_chunk** res_chunk_list; } ;
typedef  enum usnic_vnic_res_type { ____Placeholder_usnic_vnic_res_type } usnic_vnic_res_type ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct usnic_vnic_res_chunk* ERR_PTR (int /*<<< orphan*/ ) ; 

struct usnic_vnic_res_chunk*
usnic_ib_qp_grp_get_chunk(struct usnic_ib_qp_grp *qp_grp,
				enum usnic_vnic_res_type res_type)
{
	int i;

	for (i = 0; qp_grp->res_chunk_list[i]; i++) {
		if (qp_grp->res_chunk_list[i]->type == res_type)
			return qp_grp->res_chunk_list[i];
	}

	return ERR_PTR(-EINVAL);
}