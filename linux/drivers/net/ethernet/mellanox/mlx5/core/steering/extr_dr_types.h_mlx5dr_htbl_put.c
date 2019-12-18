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
struct mlx5dr_ste_htbl {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5dr_ste_htbl_free (struct mlx5dr_ste_htbl*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mlx5dr_htbl_put(struct mlx5dr_ste_htbl *htbl)
{
	if (refcount_dec_and_test(&htbl->refcount))
		mlx5dr_ste_htbl_free(htbl);
}