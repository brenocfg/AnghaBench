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
struct pasid_entry {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct pasid_entry* intel_pasid_get_entry (struct device*,int) ; 
 int /*<<< orphan*/  pasid_clear_entry (struct pasid_entry*) ; 

__attribute__((used)) static void intel_pasid_clear_entry(struct device *dev, int pasid)
{
	struct pasid_entry *pe;

	pe = intel_pasid_get_entry(dev, pasid);
	if (WARN_ON(!pe))
		return;

	pasid_clear_entry(pe);
}