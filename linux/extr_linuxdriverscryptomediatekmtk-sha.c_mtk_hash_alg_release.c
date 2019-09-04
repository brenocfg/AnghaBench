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
struct mtk_cryp {int /*<<< orphan*/  sha_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_1__ mtk_sha ; 
 int /*<<< orphan*/  mtk_sha_record_free (struct mtk_cryp*) ; 
 int /*<<< orphan*/  mtk_sha_unregister_algs () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mtk_hash_alg_release(struct mtk_cryp *cryp)
{
	spin_lock(&mtk_sha.lock);
	list_del(&cryp->sha_list);
	spin_unlock(&mtk_sha.lock);

	mtk_sha_unregister_algs();
	mtk_sha_record_free(cryp);
}