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
struct cxl {int adapter_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  adapter_idr_lock ; 
 int /*<<< orphan*/  cxl_adapter_idr ; 
 int idr_alloc (int /*<<< orphan*/ *,struct cxl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxl_alloc_adapter_nr(struct cxl *adapter)
{
	int i;

	idr_preload(GFP_KERNEL);
	spin_lock(&adapter_idr_lock);
	i = idr_alloc(&cxl_adapter_idr, adapter, 0, 0, GFP_NOWAIT);
	spin_unlock(&adapter_idr_lock);
	idr_preload_end();
	if (i < 0)
		return i;

	adapter->adapter_num = i;

	return 0;
}