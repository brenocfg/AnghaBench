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
struct mtk_cryp {TYPE_1__** sha; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_task; int /*<<< orphan*/  done_task; } ;

/* Variables and functions */
 int MTK_REC_NUM ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_sha_record_free(struct mtk_cryp *cryp)
{
	int i;

	for (i = 0; i < MTK_REC_NUM; i++) {
		tasklet_kill(&cryp->sha[i]->done_task);
		tasklet_kill(&cryp->sha[i]->queue_task);

		kfree(cryp->sha[i]);
	}
}