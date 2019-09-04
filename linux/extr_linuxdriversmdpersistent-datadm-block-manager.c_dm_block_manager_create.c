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
struct dm_block_manager {int read_only; int /*<<< orphan*/  bufio; } ;
struct buffer_aux {int dummy; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dm_block_manager* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_manager_alloc_callback ; 
 int /*<<< orphan*/  dm_block_manager_write_callback ; 
 int /*<<< orphan*/  dm_bufio_client_create (struct block_device*,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dm_block_manager*) ; 
 struct dm_block_manager* kmalloc (int,int /*<<< orphan*/ ) ; 

struct dm_block_manager *dm_block_manager_create(struct block_device *bdev,
						 unsigned block_size,
						 unsigned max_held_per_thread)
{
	int r;
	struct dm_block_manager *bm;

	bm = kmalloc(sizeof(*bm), GFP_KERNEL);
	if (!bm) {
		r = -ENOMEM;
		goto bad;
	}

	bm->bufio = dm_bufio_client_create(bdev, block_size, max_held_per_thread,
					   sizeof(struct buffer_aux),
					   dm_block_manager_alloc_callback,
					   dm_block_manager_write_callback);
	if (IS_ERR(bm->bufio)) {
		r = PTR_ERR(bm->bufio);
		kfree(bm);
		goto bad;
	}

	bm->read_only = false;

	return bm;

bad:
	return ERR_PTR(r);
}