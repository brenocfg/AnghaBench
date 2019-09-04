#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct flush_cache_sigtramp_args {unsigned long addr; int /*<<< orphan*/  page; TYPE_1__* mm; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  R4K_HIT ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int get_user_pages_fast (unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_r4k_flush_cache_sigtramp ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r4k_on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flush_cache_sigtramp_args*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r4k_flush_cache_sigtramp(unsigned long addr)
{
	struct flush_cache_sigtramp_args args;
	int npages;

	down_read(&current->mm->mmap_sem);

	npages = get_user_pages_fast(addr, 1, 0, &args.page);
	if (npages < 1)
		goto out;

	args.mm = current->mm;
	args.addr = addr;

	r4k_on_each_cpu(R4K_HIT, local_r4k_flush_cache_sigtramp, &args);

	put_page(args.page);
out:
	up_read(&current->mm->mmap_sem);
}