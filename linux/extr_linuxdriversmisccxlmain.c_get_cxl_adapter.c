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
struct cxl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  adapter_idr_lock ; 
 int /*<<< orphan*/  cxl_adapter_idr ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 struct cxl* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct cxl *get_cxl_adapter(int num)
{
	struct cxl *adapter;

	spin_lock(&adapter_idr_lock);
	if ((adapter = idr_find(&cxl_adapter_idr, num)))
		get_device(&adapter->dev);
	spin_unlock(&adapter_idr_lock);

	return adapter;
}