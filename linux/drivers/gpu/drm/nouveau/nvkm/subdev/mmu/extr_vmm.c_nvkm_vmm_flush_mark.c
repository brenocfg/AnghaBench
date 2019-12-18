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
struct nvkm_vmm_iter {scalar_t__ lvl; scalar_t__ max; int /*<<< orphan*/  flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void
nvkm_vmm_flush_mark(struct nvkm_vmm_iter *it)
{
	it->flush = min(it->flush, it->max - it->lvl);
}