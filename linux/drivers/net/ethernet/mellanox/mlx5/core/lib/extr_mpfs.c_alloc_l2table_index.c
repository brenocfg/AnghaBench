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
typedef  scalar_t__ u32 ;
struct mlx5_mpfs {scalar_t__ size; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int alloc_l2table_index(struct mlx5_mpfs *l2table, u32 *ix)
{
	int err = 0;

	*ix = find_first_zero_bit(l2table->bitmap, l2table->size);
	if (*ix >= l2table->size)
		err = -ENOSPC;
	else
		__set_bit(*ix, l2table->bitmap);

	return err;
}