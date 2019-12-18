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
struct cxl {int /*<<< orphan*/  contexts_num; int /*<<< orphan*/  adapter_num; int /*<<< orphan*/  dev; int /*<<< orphan*/  afu_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cxl_alloc_adapter_nr (struct cxl*) ; 
 int /*<<< orphan*/  cxl_remove_adapter_nr (struct cxl*) ; 
 scalar_t__ dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cxl*) ; 
 struct cxl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct cxl *cxl_alloc_adapter(void)
{
	struct cxl *adapter;

	if (!(adapter = kzalloc(sizeof(struct cxl), GFP_KERNEL)))
		return NULL;

	spin_lock_init(&adapter->afu_list_lock);

	if (cxl_alloc_adapter_nr(adapter))
		goto err1;

	if (dev_set_name(&adapter->dev, "card%i", adapter->adapter_num))
		goto err2;

	/* start with context lock taken */
	atomic_set(&adapter->contexts_num, -1);

	return adapter;
err2:
	cxl_remove_adapter_nr(adapter);
err1:
	kfree(adapter);
	return NULL;
}