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
struct binder_alloc {int /*<<< orphan*/  user_buffer_offset; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static inline ptrdiff_t
binder_alloc_get_user_buffer_offset(struct binder_alloc *alloc)
{
	/*
	 * user_buffer_offset is constant if vma is set and
	 * undefined if vma is not set. It is possible to
	 * get here with !alloc->vma if the target process
	 * is dying while a transaction is being initiated.
	 * Returning the old value is ok in this case and
	 * the transaction will fail.
	 */
	return alloc->user_buffer_offset;
}