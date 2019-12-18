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
struct tifm_adapter {int id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct tifm_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tifm_adapter_idr ; 
 int /*<<< orphan*/  tifm_adapter_lock ; 

int tifm_add_adapter(struct tifm_adapter *fm)
{
	int rc;

	idr_preload(GFP_KERNEL);
	spin_lock(&tifm_adapter_lock);
	rc = idr_alloc(&tifm_adapter_idr, fm, 0, 0, GFP_NOWAIT);
	if (rc >= 0)
		fm->id = rc;
	spin_unlock(&tifm_adapter_lock);
	idr_preload_end();
	if (rc < 0)
		return rc;

	dev_set_name(&fm->dev, "tifm%u", fm->id);
	rc = device_add(&fm->dev);
	if (rc) {
		spin_lock(&tifm_adapter_lock);
		idr_remove(&tifm_adapter_idr, fm->id);
		spin_unlock(&tifm_adapter_lock);
	}

	return rc;
}