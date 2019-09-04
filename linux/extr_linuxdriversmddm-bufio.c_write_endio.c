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
struct dm_bufio_client {int /*<<< orphan*/  async_write_error; } ;
struct dm_buffer {int /*<<< orphan*/  state; struct dm_bufio_client* c; int /*<<< orphan*/  write_error; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  B_WRITING ; 
 int /*<<< orphan*/  blk_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_endio(struct dm_buffer *b, blk_status_t status)
{
	b->write_error = status;
	if (unlikely(status)) {
		struct dm_bufio_client *c = b->c;

		(void)cmpxchg(&c->async_write_error, 0,
				blk_status_to_errno(status));
	}

	BUG_ON(!test_bit(B_WRITING, &b->state));

	smp_mb__before_atomic();
	clear_bit(B_WRITING, &b->state);
	smp_mb__after_atomic();

	wake_up_bit(&b->state, B_WRITING);
}