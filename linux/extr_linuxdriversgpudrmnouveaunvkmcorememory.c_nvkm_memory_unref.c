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
struct nvkm_memory {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_memory_del ; 

void
nvkm_memory_unref(struct nvkm_memory **pmemory)
{
	struct nvkm_memory *memory = *pmemory;
	if (memory) {
		kref_put(&memory->kref, nvkm_memory_del);
		*pmemory = NULL;
	}
}