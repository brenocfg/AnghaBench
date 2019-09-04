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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int PTRS_PER_PGD ; 
 int USER_PTRS_PER_PGD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int,int) ; 
 int swapper_pg_dir ; 

void pgd_ctor(void *x)
{
	pgd_t *pgd = x;

	memcpy(pgd + USER_PTRS_PER_PGD,
	       swapper_pg_dir + USER_PTRS_PER_PGD,
	       (PTRS_PER_PGD - USER_PTRS_PER_PGD) * sizeof(pgd_t));
}