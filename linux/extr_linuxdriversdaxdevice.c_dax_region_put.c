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
struct dax_region {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  dax_region_free ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dax_region_put(struct dax_region *dax_region)
{
	kref_put(&dax_region->kref, dax_region_free);
}