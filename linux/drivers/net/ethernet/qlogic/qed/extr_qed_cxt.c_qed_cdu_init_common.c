#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qed_hwfn {TYPE_3__* p_cxt_mngr; } ;
struct TYPE_6__ {int* task_type_size; TYPE_2__* clients; } ;
struct TYPE_4__ {int val; } ;
struct TYPE_5__ {TYPE_1__ p_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDUC_BLOCK_WASTE ; 
 int /*<<< orphan*/  CDUC_CXT_SIZE ; 
 int /*<<< orphan*/  CDUC_NCIB ; 
 int /*<<< orphan*/  CDUT_TYPE0_BLOCK_WASTE ; 
 int /*<<< orphan*/  CDUT_TYPE0_CXT_SIZE ; 
 int /*<<< orphan*/  CDUT_TYPE0_NCIB ; 
 int /*<<< orphan*/  CDUT_TYPE1_BLOCK_WASTE ; 
 int /*<<< orphan*/  CDUT_TYPE1_CXT_SIZE ; 
 int /*<<< orphan*/  CDUT_TYPE1_NCIB ; 
 int /*<<< orphan*/  CDU_REG_CID_ADDR_PARAMS_RT_OFFSET ; 
 int /*<<< orphan*/  CDU_REG_SEGMENT0_PARAMS_RT_OFFSET ; 
 int /*<<< orphan*/  CDU_REG_SEGMENT1_PARAMS_RT_OFFSET ; 
 int CONN_CXT_SIZE (struct qed_hwfn*) ; 
 size_t ILT_CLI_CDUC ; 
 size_t ILT_CLI_CDUT ; 
 int ILT_PAGE_IN_BYTES (int) ; 
 int /*<<< orphan*/  SET_FIELD (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STORE_RT_REG (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qed_cdu_init_common(struct qed_hwfn *p_hwfn)
{
	u32 page_sz, elems_per_page, block_waste, cxt_size, cdu_params = 0;

	/* CDUC - connection configuration */
	page_sz = p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC].p_size.val;
	cxt_size = CONN_CXT_SIZE(p_hwfn);
	elems_per_page = ILT_PAGE_IN_BYTES(page_sz) / cxt_size;
	block_waste = ILT_PAGE_IN_BYTES(page_sz) - elems_per_page * cxt_size;

	SET_FIELD(cdu_params, CDUC_CXT_SIZE, cxt_size);
	SET_FIELD(cdu_params, CDUC_BLOCK_WASTE, block_waste);
	SET_FIELD(cdu_params, CDUC_NCIB, elems_per_page);
	STORE_RT_REG(p_hwfn, CDU_REG_CID_ADDR_PARAMS_RT_OFFSET, cdu_params);

	/* CDUT - type-0 tasks configuration */
	page_sz = p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT].p_size.val;
	cxt_size = p_hwfn->p_cxt_mngr->task_type_size[0];
	elems_per_page = ILT_PAGE_IN_BYTES(page_sz) / cxt_size;
	block_waste = ILT_PAGE_IN_BYTES(page_sz) - elems_per_page * cxt_size;

	/* cxt size and block-waste are multipes of 8 */
	cdu_params = 0;
	SET_FIELD(cdu_params, CDUT_TYPE0_CXT_SIZE, (cxt_size >> 3));
	SET_FIELD(cdu_params, CDUT_TYPE0_BLOCK_WASTE, (block_waste >> 3));
	SET_FIELD(cdu_params, CDUT_TYPE0_NCIB, elems_per_page);
	STORE_RT_REG(p_hwfn, CDU_REG_SEGMENT0_PARAMS_RT_OFFSET, cdu_params);

	/* CDUT - type-1 tasks configuration */
	cxt_size = p_hwfn->p_cxt_mngr->task_type_size[1];
	elems_per_page = ILT_PAGE_IN_BYTES(page_sz) / cxt_size;
	block_waste = ILT_PAGE_IN_BYTES(page_sz) - elems_per_page * cxt_size;

	/* cxt size and block-waste are multipes of 8 */
	cdu_params = 0;
	SET_FIELD(cdu_params, CDUT_TYPE1_CXT_SIZE, (cxt_size >> 3));
	SET_FIELD(cdu_params, CDUT_TYPE1_BLOCK_WASTE, (block_waste >> 3));
	SET_FIELD(cdu_params, CDUT_TYPE1_NCIB, elems_per_page);
	STORE_RT_REG(p_hwfn, CDU_REG_SEGMENT1_PARAMS_RT_OFFSET, cdu_params);
}