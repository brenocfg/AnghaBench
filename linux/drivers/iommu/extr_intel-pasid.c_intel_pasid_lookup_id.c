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

/* Variables and functions */
 void* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pasid_idr ; 
 int /*<<< orphan*/  pasid_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void *intel_pasid_lookup_id(int pasid)
{
	void *p;

	spin_lock(&pasid_lock);
	p = idr_find(&pasid_idr, pasid);
	spin_unlock(&pasid_lock);

	return p;
}