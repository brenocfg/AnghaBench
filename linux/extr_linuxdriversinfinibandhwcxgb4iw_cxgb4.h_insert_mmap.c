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
struct c4iw_ucontext {int /*<<< orphan*/  mmap_lock; int /*<<< orphan*/  mmaps; } ;
struct c4iw_mm_entry {int /*<<< orphan*/  entry; int /*<<< orphan*/  len; scalar_t__ addr; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void insert_mmap(struct c4iw_ucontext *ucontext,
			       struct c4iw_mm_entry *mm)
{
	spin_lock(&ucontext->mmap_lock);
	pr_debug("key 0x%x addr 0x%llx len %d\n",
		 mm->key, (unsigned long long)mm->addr, mm->len);
	list_add_tail(&mm->entry, &ucontext->mmaps);
	spin_unlock(&ucontext->mmap_lock);
}