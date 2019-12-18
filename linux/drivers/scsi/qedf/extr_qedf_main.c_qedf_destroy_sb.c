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
struct qedf_fastpath {scalar_t__ sb_id; struct qedf_fastpath* sb_info; } ;
struct qedf_ctx {int num_queues; struct qedf_fastpath* fp_array; } ;

/* Variables and functions */
 scalar_t__ QEDF_SB_ID_NULL ; 
 int /*<<< orphan*/  kfree (struct qedf_fastpath*) ; 
 int /*<<< orphan*/  qedf_free_sb (struct qedf_ctx*,struct qedf_fastpath*) ; 

__attribute__((used)) static void qedf_destroy_sb(struct qedf_ctx *qedf)
{
	int id;
	struct qedf_fastpath *fp = NULL;

	for (id = 0; id < qedf->num_queues; id++) {
		fp = &(qedf->fp_array[id]);
		if (fp->sb_id == QEDF_SB_ID_NULL)
			break;
		qedf_free_sb(qedf, fp->sb_info);
		kfree(fp->sb_info);
	}
	kfree(qedf->fp_array);
}