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
struct buffer_aux {int write_locked; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int bl_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bl_up_write (int /*<<< orphan*/ *) ; 
 int dm_bm_validate_buffer (struct dm_block_manager*,int /*<<< orphan*/ ,struct buffer_aux*,struct dm_block_validator*) ; 
 struct buffer_aux* dm_bufio_get_aux_data (int /*<<< orphan*/ ) ; 
 void* dm_bufio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_buffer**) ; 
 int /*<<< orphan*/  dm_bufio_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_recursive_bug (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_buffer (struct dm_block*) ; 
 scalar_t__ unlikely (int) ; 

int dm_bm_write_lock(struct dm_block_manager *bm,
		     dm_block_t b, struct dm_block_validator *v,
		     struct dm_block **result)
{
	struct buffer_aux *aux;
	void *p;
	int r;

	if (bm->read_only)
		return -EPERM;

	p = dm_bufio_read(bm->bufio, b, (struct dm_buffer **) result);
	if (IS_ERR(p))
		return PTR_ERR(p);

	aux = dm_bufio_get_aux_data(to_buffer(*result));
	r = bl_down_write(&aux->lock);
	if (r) {
		dm_bufio_release(to_buffer(*result));
		report_recursive_bug(b, r);
		return r;
	}

	aux->write_locked = 1;

	r = dm_bm_validate_buffer(bm, to_buffer(*result), aux, v);
	if (unlikely(r)) {
		bl_up_write(&aux->lock);
		dm_bufio_release(to_buffer(*result));
		return r;
	}

	return 0;
}