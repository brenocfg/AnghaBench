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
typedef  size_t u32 ;
struct TYPE_8__ {int /*<<< orphan*/  val; void* reg; } ;
struct TYPE_7__ {void* reg; } ;
struct TYPE_6__ {void* reg; } ;
struct qed_ilt_client_cfg {TYPE_3__ p_size; TYPE_2__ last; TYPE_1__ first; } ;
struct qed_hwfn {struct qed_cxt_mngr* p_cxt_mngr; TYPE_5__* cdev; } ;
struct qed_cxt_mngr {int /*<<< orphan*/  mutex; int /*<<< orphan*/  vf_count; int /*<<< orphan*/ * task_type_size; struct qed_ilt_client_cfg* clients; } ;
struct TYPE_10__ {TYPE_4__* p_iov_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  total_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDUC ; 
 int /*<<< orphan*/  CDUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIRST_ILT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* ILT_CFG_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ILT_CLI_CDUC ; 
 size_t ILT_CLI_CDUT ; 
 size_t ILT_CLI_MAX ; 
 size_t ILT_CLI_QM ; 
 size_t ILT_CLI_SRC ; 
 size_t ILT_CLI_TM ; 
 size_t ILT_CLI_TSDM ; 
 int /*<<< orphan*/  ILT_DEFAULT_HW_P_SIZE ; 
 int /*<<< orphan*/  LAST_ILT ; 
 int /*<<< orphan*/  P_SIZE ; 
 int /*<<< orphan*/  QM ; 
 int /*<<< orphan*/  SRC ; 
 int /*<<< orphan*/  TM ; 
 int /*<<< orphan*/  TSDM ; 
 int /*<<< orphan*/  TYPE0_TASK_CXT_SIZE (struct qed_hwfn*) ; 
 int /*<<< orphan*/  TYPE1_TASK_CXT_SIZE (struct qed_hwfn*) ; 
 struct qed_cxt_mngr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int qed_cxt_mngr_alloc(struct qed_hwfn *p_hwfn)
{
	struct qed_ilt_client_cfg *clients;
	struct qed_cxt_mngr *p_mngr;
	u32 i;

	p_mngr = kzalloc(sizeof(*p_mngr), GFP_KERNEL);
	if (!p_mngr)
		return -ENOMEM;

	/* Initialize ILT client registers */
	clients = p_mngr->clients;
	clients[ILT_CLI_CDUC].first.reg = ILT_CFG_REG(CDUC, FIRST_ILT);
	clients[ILT_CLI_CDUC].last.reg = ILT_CFG_REG(CDUC, LAST_ILT);
	clients[ILT_CLI_CDUC].p_size.reg = ILT_CFG_REG(CDUC, P_SIZE);

	clients[ILT_CLI_QM].first.reg = ILT_CFG_REG(QM, FIRST_ILT);
	clients[ILT_CLI_QM].last.reg = ILT_CFG_REG(QM, LAST_ILT);
	clients[ILT_CLI_QM].p_size.reg = ILT_CFG_REG(QM, P_SIZE);

	clients[ILT_CLI_TM].first.reg = ILT_CFG_REG(TM, FIRST_ILT);
	clients[ILT_CLI_TM].last.reg = ILT_CFG_REG(TM, LAST_ILT);
	clients[ILT_CLI_TM].p_size.reg = ILT_CFG_REG(TM, P_SIZE);

	clients[ILT_CLI_SRC].first.reg = ILT_CFG_REG(SRC, FIRST_ILT);
	clients[ILT_CLI_SRC].last.reg = ILT_CFG_REG(SRC, LAST_ILT);
	clients[ILT_CLI_SRC].p_size.reg = ILT_CFG_REG(SRC, P_SIZE);

	clients[ILT_CLI_CDUT].first.reg = ILT_CFG_REG(CDUT, FIRST_ILT);
	clients[ILT_CLI_CDUT].last.reg = ILT_CFG_REG(CDUT, LAST_ILT);
	clients[ILT_CLI_CDUT].p_size.reg = ILT_CFG_REG(CDUT, P_SIZE);

	clients[ILT_CLI_TSDM].first.reg = ILT_CFG_REG(TSDM, FIRST_ILT);
	clients[ILT_CLI_TSDM].last.reg = ILT_CFG_REG(TSDM, LAST_ILT);
	clients[ILT_CLI_TSDM].p_size.reg = ILT_CFG_REG(TSDM, P_SIZE);
	/* default ILT page size for all clients is 64K */
	for (i = 0; i < ILT_CLI_MAX; i++)
		p_mngr->clients[i].p_size.val = ILT_DEFAULT_HW_P_SIZE;

	/* Initialize task sizes */
	p_mngr->task_type_size[0] = TYPE0_TASK_CXT_SIZE(p_hwfn);
	p_mngr->task_type_size[1] = TYPE1_TASK_CXT_SIZE(p_hwfn);

	if (p_hwfn->cdev->p_iov_info)
		p_mngr->vf_count = p_hwfn->cdev->p_iov_info->total_vfs;
	/* Initialize the dynamic ILT allocation mutex */
	mutex_init(&p_mngr->mutex);

	/* Set the cxt mangr pointer priori to further allocations */
	p_hwfn->p_cxt_mngr = p_mngr;

	return 0;
}