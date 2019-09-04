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
struct dmaengine_unmap_data {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_unmap ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dmaengine_unmap_put(struct dmaengine_unmap_data *unmap)
{
	if (unmap)
		kref_put(&unmap->kref, dmaengine_unmap);
}