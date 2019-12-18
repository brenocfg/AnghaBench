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
typedef  scalar_t__ u64 ;
struct efa_ucontext {int /*<<< orphan*/  mmap_xa; } ;
struct efa_mmap_entry {scalar_t__ length; int /*<<< orphan*/  address; int /*<<< orphan*/  obj; } ;
struct efa_dev {int /*<<< orphan*/  ibdev; } ;

/* Variables and functions */
 scalar_t__ EFA_MMAP_PAGE_MASK ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ U32_MAX ; 
 scalar_t__ get_mmap_key (struct efa_mmap_entry*) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct efa_mmap_entry* xa_load (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static struct efa_mmap_entry *mmap_entry_get(struct efa_dev *dev,
					     struct efa_ucontext *ucontext,
					     u64 key, u64 len)
{
	struct efa_mmap_entry *entry;
	u64 mmap_page;

	mmap_page = (key & EFA_MMAP_PAGE_MASK) >> PAGE_SHIFT;
	if (mmap_page > U32_MAX)
		return NULL;

	entry = xa_load(&ucontext->mmap_xa, mmap_page);
	if (!entry || get_mmap_key(entry) != key || entry->length != len)
		return NULL;

	ibdev_dbg(&dev->ibdev,
		  "mmap: obj[0x%p] key[%#llx] addr[%#llx] len[%#llx] removed\n",
		  entry->obj, key, entry->address, entry->length);

	return entry;
}