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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_page (void*,void*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 

__attribute__((used)) static void v6_copy_user_highpage_nonaliasing(struct page *to,
	struct page *from, unsigned long vaddr, struct vm_area_struct *vma)
{
	void *kto, *kfrom;

	kfrom = kmap_atomic(from);
	kto = kmap_atomic(to);
	copy_page(kto, kfrom);
	kunmap_atomic(kto);
	kunmap_atomic(kfrom);
}