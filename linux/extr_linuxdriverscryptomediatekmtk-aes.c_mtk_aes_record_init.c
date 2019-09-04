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
struct mtk_cryp {struct mtk_aes_rec** aes; } ;
struct mtk_aes_rec {void* buf; int /*<<< orphan*/  id; int /*<<< orphan*/  done_task; int /*<<< orphan*/  queue_task; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; struct mtk_cryp* cryp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BUF_ORDER ; 
 int /*<<< orphan*/  AES_QUEUE_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MTK_REC_NUM ; 
 int /*<<< orphan*/  MTK_RING0 ; 
 int /*<<< orphan*/  MTK_RING1 ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct mtk_aes_rec*) ; 
 struct mtk_aes_rec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_aes_done_task ; 
 int /*<<< orphan*/  mtk_aes_queue_task ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int mtk_aes_record_init(struct mtk_cryp *cryp)
{
	struct mtk_aes_rec **aes = cryp->aes;
	int i, err = -ENOMEM;

	for (i = 0; i < MTK_REC_NUM; i++) {
		aes[i] = kzalloc(sizeof(**aes), GFP_KERNEL);
		if (!aes[i])
			goto err_cleanup;

		aes[i]->buf = (void *)__get_free_pages(GFP_KERNEL,
						AES_BUF_ORDER);
		if (!aes[i]->buf)
			goto err_cleanup;

		aes[i]->cryp = cryp;

		spin_lock_init(&aes[i]->lock);
		crypto_init_queue(&aes[i]->queue, AES_QUEUE_SIZE);

		tasklet_init(&aes[i]->queue_task, mtk_aes_queue_task,
			     (unsigned long)aes[i]);
		tasklet_init(&aes[i]->done_task, mtk_aes_done_task,
			     (unsigned long)aes[i]);
	}

	/* Link to ring0 and ring1 respectively */
	aes[0]->id = MTK_RING0;
	aes[1]->id = MTK_RING1;

	return 0;

err_cleanup:
	for (; i--; ) {
		free_page((unsigned long)aes[i]->buf);
		kfree(aes[i]);
	}

	return err;
}