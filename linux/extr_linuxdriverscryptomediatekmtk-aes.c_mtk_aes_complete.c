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
struct mtk_cryp {int dummy; } ;
struct mtk_aes_rec {int /*<<< orphan*/  queue_task; TYPE_1__* areq; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AES_FLAGS_BUSY ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int mtk_aes_complete(struct mtk_cryp *cryp,
				   struct mtk_aes_rec *aes,
				   int err)
{
	aes->flags &= ~AES_FLAGS_BUSY;
	aes->areq->complete(aes->areq, err);
	/* Handle new request */
	tasklet_schedule(&aes->queue_task);
	return err;
}