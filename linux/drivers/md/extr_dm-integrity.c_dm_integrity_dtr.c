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
struct skcipher_request {int /*<<< orphan*/  iv; } ;
struct dm_target {struct dm_integrity_c* private; } ;
struct dm_integrity_c {unsigned int journal_sections; int /*<<< orphan*/  journal_mac_alg; scalar_t__ journal_mac; int /*<<< orphan*/  journal_crypt_alg; scalar_t__ journal_crypt; int /*<<< orphan*/  internal_hash_alg; scalar_t__ internal_hash; scalar_t__ sb; struct skcipher_request** journal_tree; struct skcipher_request** sk_requests; scalar_t__ journal_io_scatterlist; scalar_t__ journal_scatterlist; int /*<<< orphan*/  may_write_bitmap; int /*<<< orphan*/  recalc_bitmap; int /*<<< orphan*/  journal_xor; int /*<<< orphan*/  journal_io; int /*<<< orphan*/  journal; scalar_t__ meta_dev; scalar_t__ dev; scalar_t__ io; int /*<<< orphan*/  journal_io_mempool; scalar_t__ bufio; struct skcipher_request** bbs; struct skcipher_request** recalc_tags; int /*<<< orphan*/  recalc_buffer; scalar_t__ recalc_wq; scalar_t__ writer_wq; scalar_t__ commit_wq; scalar_t__ wait_wq; scalar_t__ metadata_wq; int /*<<< orphan*/  wait_list; int /*<<< orphan*/  in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int SB_SECTORS ; 
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  crypto_free_shash (scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_skcipher (scalar_t__) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  dm_bufio_client_destroy (scalar_t__) ; 
 int /*<<< orphan*/  dm_integrity_free_journal_scatterlist (struct dm_integrity_c*,scalar_t__) ; 
 int /*<<< orphan*/  dm_integrity_free_page_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_io_client_destroy (scalar_t__) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,scalar_t__) ; 
 int /*<<< orphan*/  free_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pages_exact (scalar_t__,int) ; 
 int /*<<< orphan*/  kfree (struct dm_integrity_c*) ; 
 int /*<<< orphan*/  kvfree (struct skcipher_request**) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_integrity_dtr(struct dm_target *ti)
{
	struct dm_integrity_c *ic = ti->private;

	BUG_ON(!RB_EMPTY_ROOT(&ic->in_progress));
	BUG_ON(!list_empty(&ic->wait_list));

	if (ic->metadata_wq)
		destroy_workqueue(ic->metadata_wq);
	if (ic->wait_wq)
		destroy_workqueue(ic->wait_wq);
	if (ic->commit_wq)
		destroy_workqueue(ic->commit_wq);
	if (ic->writer_wq)
		destroy_workqueue(ic->writer_wq);
	if (ic->recalc_wq)
		destroy_workqueue(ic->recalc_wq);
	vfree(ic->recalc_buffer);
	kvfree(ic->recalc_tags);
	kvfree(ic->bbs);
	if (ic->bufio)
		dm_bufio_client_destroy(ic->bufio);
	mempool_exit(&ic->journal_io_mempool);
	if (ic->io)
		dm_io_client_destroy(ic->io);
	if (ic->dev)
		dm_put_device(ti, ic->dev);
	if (ic->meta_dev)
		dm_put_device(ti, ic->meta_dev);
	dm_integrity_free_page_list(ic->journal);
	dm_integrity_free_page_list(ic->journal_io);
	dm_integrity_free_page_list(ic->journal_xor);
	dm_integrity_free_page_list(ic->recalc_bitmap);
	dm_integrity_free_page_list(ic->may_write_bitmap);
	if (ic->journal_scatterlist)
		dm_integrity_free_journal_scatterlist(ic, ic->journal_scatterlist);
	if (ic->journal_io_scatterlist)
		dm_integrity_free_journal_scatterlist(ic, ic->journal_io_scatterlist);
	if (ic->sk_requests) {
		unsigned i;

		for (i = 0; i < ic->journal_sections; i++) {
			struct skcipher_request *req = ic->sk_requests[i];
			if (req) {
				kzfree(req->iv);
				skcipher_request_free(req);
			}
		}
		kvfree(ic->sk_requests);
	}
	kvfree(ic->journal_tree);
	if (ic->sb)
		free_pages_exact(ic->sb, SB_SECTORS << SECTOR_SHIFT);

	if (ic->internal_hash)
		crypto_free_shash(ic->internal_hash);
	free_alg(&ic->internal_hash_alg);

	if (ic->journal_crypt)
		crypto_free_skcipher(ic->journal_crypt);
	free_alg(&ic->journal_crypt_alg);

	if (ic->journal_mac)
		crypto_free_shash(ic->journal_mac);
	free_alg(&ic->journal_mac_alg);

	kfree(ic);
}