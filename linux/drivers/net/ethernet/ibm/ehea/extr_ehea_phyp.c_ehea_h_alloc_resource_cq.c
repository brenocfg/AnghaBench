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
typedef  unsigned long u64 ;
struct h_epas {int dummy; } ;
struct ehea_cq_attr {unsigned long act_nr_of_cqes; unsigned long nr_pages; int /*<<< orphan*/  max_nr_of_cqes; int /*<<< orphan*/  cq_token; int /*<<< orphan*/  eq_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_ALLOC_HEA_RESOURCE ; 
 int /*<<< orphan*/  H_ALL_RES_TYPE_CQ ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 unsigned long ehea_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,unsigned long const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcp_epas_ctor (struct h_epas*,unsigned long,unsigned long) ; 

u64 ehea_h_alloc_resource_cq(const u64 adapter_handle,
			     struct ehea_cq_attr *cq_attr,
			     u64 *cq_handle, struct h_epas *epas)
{
	u64 hret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	hret = ehea_plpar_hcall9(H_ALLOC_HEA_RESOURCE,
				 outs,
				 adapter_handle,		/* R4 */
				 H_ALL_RES_TYPE_CQ,		/* R5 */
				 cq_attr->eq_handle,		/* R6 */
				 cq_attr->cq_token,		/* R7 */
				 cq_attr->max_nr_of_cqes,	/* R8 */
				 0, 0, 0, 0);			/* R9-R12 */

	*cq_handle = outs[0];
	cq_attr->act_nr_of_cqes = outs[3];
	cq_attr->nr_pages = outs[4];

	if (!hret)
		hcp_epas_ctor(epas, outs[5], outs[6]);

	return hret;
}