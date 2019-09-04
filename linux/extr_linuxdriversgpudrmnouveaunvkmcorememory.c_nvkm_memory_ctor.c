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
struct nvkm_memory_func {int dummy; } ;
struct nvkm_memory {int /*<<< orphan*/  kref; struct nvkm_memory_func const* func; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

void
nvkm_memory_ctor(const struct nvkm_memory_func *func,
		 struct nvkm_memory *memory)
{
	memory->func = func;
	kref_init(&memory->kref);
}