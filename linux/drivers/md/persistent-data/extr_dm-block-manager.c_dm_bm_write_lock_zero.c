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
struct dm_buffer {int dummy; } ;
struct dm_block_validator {int dummy; } ;
struct dm_block_manager {int /*<<< orphan*/  bufio; scalar_t__ read_only; } ;
struct dm_block {int dummy; } ;
struct buffer_aux {int write_locked; struct dm_block_validator* validator; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int bl_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_bm_block_size (struct dm_block_manager*) ; 
 struct buffer_aux* dm_bufio_get_aux_data (int /*<<< orphan*/ ) ; 
 void* dm_bufio_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_buffer**) ; 
 int /*<<< orphan*/  dm_bufio_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_buffer (struct dm_block*) ; 

int dm_bm_write_lock_zero(struct dm_block_manager *bm,
			  dm_block_t b, struct dm_block_validator *v,
			  struct dm_block **result)
{
	int r;
	struct buffer_aux *aux;
	void *p;

	if (bm->read_only)
		return -EPERM;

	p = dm_bufio_new(bm->bufio, b, (struct dm_buffer **) result);
	if (IS_ERR(p))
		return PTR_ERR(p);

	memset(p, 0, dm_bm_block_size(bm));

	aux = dm_bufio_get_aux_data(to_buffer(*result));
	r = bl_down_write(&aux->lock);
	if (r) {
		dm_bufio_release(to_buffer(*result));
		return r;
	}

	aux->write_locked = 1;
	aux->validator = v;

	return 0;
}