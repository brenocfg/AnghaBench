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
struct mlx5dr_ste_htbl {int /*<<< orphan*/  chunk; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_ste_htbl*) ; 
 int /*<<< orphan*/  mlx5dr_icm_free_chunk (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

int mlx5dr_ste_htbl_free(struct mlx5dr_ste_htbl *htbl)
{
	if (refcount_read(&htbl->refcount))
		return -EBUSY;

	mlx5dr_icm_free_chunk(htbl->chunk);
	kfree(htbl);
	return 0;
}