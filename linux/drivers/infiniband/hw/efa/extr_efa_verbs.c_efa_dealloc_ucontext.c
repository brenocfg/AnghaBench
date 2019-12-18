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
struct ib_ucontext {int /*<<< orphan*/  device; } ;
struct efa_ucontext {int /*<<< orphan*/  uarn; } ;
struct efa_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  efa_dealloc_uar (struct efa_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmap_entries_remove_free (struct efa_dev*,struct efa_ucontext*) ; 
 struct efa_dev* to_edev (int /*<<< orphan*/ ) ; 
 struct efa_ucontext* to_eucontext (struct ib_ucontext*) ; 

void efa_dealloc_ucontext(struct ib_ucontext *ibucontext)
{
	struct efa_ucontext *ucontext = to_eucontext(ibucontext);
	struct efa_dev *dev = to_edev(ibucontext->device);

	mmap_entries_remove_free(dev, ucontext);
	efa_dealloc_uar(dev, ucontext->uarn);
}