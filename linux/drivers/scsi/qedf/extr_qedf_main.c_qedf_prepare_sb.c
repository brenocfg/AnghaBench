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
struct qedf_fastpath {int sb_id; int cq_num_entries; struct qedf_ctx* qedf; void* sb_info; } ;
struct qedf_ctx {int num_queues; TYPE_1__** global_queues; int /*<<< orphan*/  dbg_ctx; struct qedf_fastpath* fp_array; } ;
struct fcoe_cqe {int dummy; } ;
struct TYPE_2__ {int cq_mem_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int QEDF_SB_ID_NULL ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int qedf_alloc_and_init_sb (struct qedf_ctx*,void*,int) ; 

__attribute__((used)) static int qedf_prepare_sb(struct qedf_ctx *qedf)
{
	int id;
	struct qedf_fastpath *fp;
	int ret;

	qedf->fp_array =
	    kcalloc(qedf->num_queues, sizeof(struct qedf_fastpath),
		GFP_KERNEL);

	if (!qedf->fp_array) {
		QEDF_ERR(&(qedf->dbg_ctx), "fastpath array allocation "
			  "failed.\n");
		return -ENOMEM;
	}

	for (id = 0; id < qedf->num_queues; id++) {
		fp = &(qedf->fp_array[id]);
		fp->sb_id = QEDF_SB_ID_NULL;
		fp->sb_info = kcalloc(1, sizeof(*fp->sb_info), GFP_KERNEL);
		if (!fp->sb_info) {
			QEDF_ERR(&(qedf->dbg_ctx), "SB info struct "
				  "allocation failed.\n");
			goto err;
		}
		ret = qedf_alloc_and_init_sb(qedf, fp->sb_info, id);
		if (ret) {
			QEDF_ERR(&(qedf->dbg_ctx), "SB allocation and "
				  "initialization failed.\n");
			goto err;
		}
		fp->sb_id = id;
		fp->qedf = qedf;
		fp->cq_num_entries =
		    qedf->global_queues[id]->cq_mem_size /
		    sizeof(struct fcoe_cqe);
	}
err:
	return 0;
}