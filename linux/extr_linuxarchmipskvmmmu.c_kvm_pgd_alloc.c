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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PGD_ORDER ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_pgd_init (int /*<<< orphan*/ *) ; 

pgd_t *kvm_pgd_alloc(void)
{
	pgd_t *ret;

	ret = (pgd_t *)__get_free_pages(GFP_KERNEL, PGD_ORDER);
	if (ret)
		kvm_pgd_init(ret);

	return ret;
}