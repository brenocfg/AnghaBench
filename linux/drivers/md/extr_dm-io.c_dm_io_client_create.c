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
struct dm_io_client {int /*<<< orphan*/  pool; int /*<<< orphan*/  bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOSET_NEED_BVECS ; 
 int ENOMEM ; 
 struct dm_io_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _dm_io_cache ; 
 int bioset_init (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int dm_get_reserved_bio_based_ios () ; 
 int /*<<< orphan*/  kfree (struct dm_io_client*) ; 
 struct dm_io_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int mempool_init_slab_pool (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

struct dm_io_client *dm_io_client_create(void)
{
	struct dm_io_client *client;
	unsigned min_ios = dm_get_reserved_bio_based_ios();
	int ret;

	client = kzalloc(sizeof(*client), GFP_KERNEL);
	if (!client)
		return ERR_PTR(-ENOMEM);

	ret = mempool_init_slab_pool(&client->pool, min_ios, _dm_io_cache);
	if (ret)
		goto bad;

	ret = bioset_init(&client->bios, min_ios, 0, BIOSET_NEED_BVECS);
	if (ret)
		goto bad;

	return client;

   bad:
	mempool_exit(&client->pool);
	kfree(client);
	return ERR_PTR(ret);
}