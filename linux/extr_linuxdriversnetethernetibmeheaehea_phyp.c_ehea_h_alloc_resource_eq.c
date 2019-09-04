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
typedef  int u64 ;
struct ehea_eq_attr {unsigned long act_nr_of_eqes; unsigned long nr_pages; unsigned long ist1; unsigned long ist2; unsigned long ist3; unsigned long ist4; int /*<<< orphan*/  max_nr_of_eqes; int /*<<< orphan*/  eqe_gen; scalar_t__ type; } ;

/* Variables and functions */
 int EHEA_BMASK_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  H_ALLOC_HEA_RESOURCE ; 
 int /*<<< orphan*/  H_ALL_RES_EQ_INH_EQE_GEN ; 
 int /*<<< orphan*/  H_ALL_RES_EQ_NEQ ; 
 int /*<<< orphan*/  H_ALL_RES_EQ_NON_NEQ_ISN ; 
 int /*<<< orphan*/  H_ALL_RES_EQ_RES_TYPE ; 
 int H_ALL_RES_TYPE_EQ ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int ehea_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 ehea_h_alloc_resource_eq(const u64 adapter_handle,
			     struct ehea_eq_attr *eq_attr, u64 *eq_handle)
{
	u64 hret, allocate_controls;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	/* resource type */
	allocate_controls =
	    EHEA_BMASK_SET(H_ALL_RES_EQ_RES_TYPE, H_ALL_RES_TYPE_EQ)
	    | EHEA_BMASK_SET(H_ALL_RES_EQ_NEQ, eq_attr->type ? 1 : 0)
	    | EHEA_BMASK_SET(H_ALL_RES_EQ_INH_EQE_GEN, !eq_attr->eqe_gen)
	    | EHEA_BMASK_SET(H_ALL_RES_EQ_NON_NEQ_ISN, 1);

	hret = ehea_plpar_hcall9(H_ALLOC_HEA_RESOURCE,
				 outs,
				 adapter_handle,		/* R4 */
				 allocate_controls,		/* R5 */
				 eq_attr->max_nr_of_eqes,	/* R6 */
				 0, 0, 0, 0, 0, 0);		/* R7-R10 */

	*eq_handle = outs[0];
	eq_attr->act_nr_of_eqes = outs[3];
	eq_attr->nr_pages = outs[4];
	eq_attr->ist1 = outs[5];
	eq_attr->ist2 = outs[6];
	eq_attr->ist3 = outs[7];
	eq_attr->ist4 = outs[8];

	return hret;
}