#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
struct mpt3sas_facts {scalar_t__ MaxDevHandle; } ;
struct TYPE_2__ {scalar_t__ MaxDevHandle; } ;
struct MPT3SAS_ADAPTER {int pd_handles_sz; int pend_os_device_add_sz; int device_remove_in_progress_sz; TYPE_1__ facts; struct mpt3sas_facts prev_fw_facts; void* device_remove_in_progress; void* pend_os_device_add; void* blocking_handles; void* pd_handles; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,void*) ; 
 void* krealloc (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct mpt3sas_facts*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
_base_check_ioc_facts_changes(struct MPT3SAS_ADAPTER *ioc)
{
	u16 pd_handles_sz;
	void *pd_handles = NULL, *blocking_handles = NULL;
	void *pend_os_device_add = NULL, *device_remove_in_progress = NULL;
	struct mpt3sas_facts *old_facts = &ioc->prev_fw_facts;

	if (ioc->facts.MaxDevHandle > old_facts->MaxDevHandle) {
		pd_handles_sz = (ioc->facts.MaxDevHandle / 8);
		if (ioc->facts.MaxDevHandle % 8)
			pd_handles_sz++;

		pd_handles = krealloc(ioc->pd_handles, pd_handles_sz,
		    GFP_KERNEL);
		if (!pd_handles) {
			ioc_info(ioc,
			    "Unable to allocate the memory for pd_handles of sz: %d\n",
			    pd_handles_sz);
			return -ENOMEM;
		}
		memset(pd_handles + ioc->pd_handles_sz, 0,
		    (pd_handles_sz - ioc->pd_handles_sz));
		ioc->pd_handles = pd_handles;

		blocking_handles = krealloc(ioc->blocking_handles,
		    pd_handles_sz, GFP_KERNEL);
		if (!blocking_handles) {
			ioc_info(ioc,
			    "Unable to allocate the memory for "
			    "blocking_handles of sz: %d\n",
			    pd_handles_sz);
			return -ENOMEM;
		}
		memset(blocking_handles + ioc->pd_handles_sz, 0,
		    (pd_handles_sz - ioc->pd_handles_sz));
		ioc->blocking_handles = blocking_handles;
		ioc->pd_handles_sz = pd_handles_sz;

		pend_os_device_add = krealloc(ioc->pend_os_device_add,
		    pd_handles_sz, GFP_KERNEL);
		if (!pend_os_device_add) {
			ioc_info(ioc,
			    "Unable to allocate the memory for pend_os_device_add of sz: %d\n",
			    pd_handles_sz);
			return -ENOMEM;
		}
		memset(pend_os_device_add + ioc->pend_os_device_add_sz, 0,
		    (pd_handles_sz - ioc->pend_os_device_add_sz));
		ioc->pend_os_device_add = pend_os_device_add;
		ioc->pend_os_device_add_sz = pd_handles_sz;

		device_remove_in_progress = krealloc(
		    ioc->device_remove_in_progress, pd_handles_sz, GFP_KERNEL);
		if (!device_remove_in_progress) {
			ioc_info(ioc,
			    "Unable to allocate the memory for "
			    "device_remove_in_progress of sz: %d\n "
			    , pd_handles_sz);
			return -ENOMEM;
		}
		memset(device_remove_in_progress +
		    ioc->device_remove_in_progress_sz, 0,
		    (pd_handles_sz - ioc->device_remove_in_progress_sz));
		ioc->device_remove_in_progress = device_remove_in_progress;
		ioc->device_remove_in_progress_sz = pd_handles_sz;
	}

	memcpy(&ioc->prev_fw_facts, &ioc->facts, sizeof(struct mpt3sas_facts));
	return 0;
}