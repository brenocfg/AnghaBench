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
struct dm_target {struct crypt_config* private; } ;
struct crypt_config {int /*<<< orphan*/  bio_alloc_lock; struct crypt_config* authenc_key; struct crypt_config* cipher_auth; struct crypt_config* key_string; struct crypt_config* cipher_string; scalar_t__ dev; TYPE_1__* iv_gen_ops; int /*<<< orphan*/  n_allocated_pages; int /*<<< orphan*/  tag_pool; int /*<<< orphan*/  req_pool; int /*<<< orphan*/  page_pool; int /*<<< orphan*/  bs; scalar_t__ crypt_queue; scalar_t__ io_queue; scalar_t__ write_thread; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dtr ) (struct crypt_config*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypt_calculate_pages_per_client () ; 
 int /*<<< orphan*/  crypt_free_tfms (struct crypt_config*) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  dm_crypt_clients_lock ; 
 int /*<<< orphan*/  dm_crypt_clients_n ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,scalar_t__) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  kzfree (struct crypt_config*) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_counter_sum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct crypt_config*) ; 

__attribute__((used)) static void crypt_dtr(struct dm_target *ti)
{
	struct crypt_config *cc = ti->private;

	ti->private = NULL;

	if (!cc)
		return;

	if (cc->write_thread)
		kthread_stop(cc->write_thread);

	if (cc->io_queue)
		destroy_workqueue(cc->io_queue);
	if (cc->crypt_queue)
		destroy_workqueue(cc->crypt_queue);

	crypt_free_tfms(cc);

	bioset_exit(&cc->bs);

	mempool_exit(&cc->page_pool);
	mempool_exit(&cc->req_pool);
	mempool_exit(&cc->tag_pool);

	WARN_ON(percpu_counter_sum(&cc->n_allocated_pages) != 0);
	percpu_counter_destroy(&cc->n_allocated_pages);

	if (cc->iv_gen_ops && cc->iv_gen_ops->dtr)
		cc->iv_gen_ops->dtr(cc);

	if (cc->dev)
		dm_put_device(ti, cc->dev);

	kzfree(cc->cipher_string);
	kzfree(cc->key_string);
	kzfree(cc->cipher_auth);
	kzfree(cc->authenc_key);

	mutex_destroy(&cc->bio_alloc_lock);

	/* Must zero key material before freeing */
	kzfree(cc);

	spin_lock(&dm_crypt_clients_lock);
	WARN_ON(!dm_crypt_clients_n);
	dm_crypt_clients_n--;
	crypt_calculate_pages_per_client();
	spin_unlock(&dm_crypt_clients_lock);
}