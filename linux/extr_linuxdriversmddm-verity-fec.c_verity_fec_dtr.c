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
struct dm_verity_fec {scalar_t__ dev; scalar_t__ bufio; scalar_t__ data_bufio; int /*<<< orphan*/  cache; int /*<<< orphan*/  extra_pool; int /*<<< orphan*/  prealloc_pool; int /*<<< orphan*/  rs_pool; } ;
struct dm_verity {struct dm_verity_fec* fec; int /*<<< orphan*/  ti; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_bufio_client_destroy (scalar_t__) ; 
 int /*<<< orphan*/  dm_put_device (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dm_verity_fec*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verity_fec_is_enabled (struct dm_verity*) ; 

void verity_fec_dtr(struct dm_verity *v)
{
	struct dm_verity_fec *f = v->fec;

	if (!verity_fec_is_enabled(v))
		goto out;

	mempool_exit(&f->rs_pool);
	mempool_exit(&f->prealloc_pool);
	mempool_exit(&f->extra_pool);
	kmem_cache_destroy(f->cache);

	if (f->data_bufio)
		dm_bufio_client_destroy(f->data_bufio);
	if (f->bufio)
		dm_bufio_client_destroy(f->bufio);

	if (f->dev)
		dm_put_device(v->ti, f->dev);
out:
	kfree(f);
	v->fec = NULL;
}