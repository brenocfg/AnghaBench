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
struct ramfuc {int /*<<< orphan*/  memx; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_memx_wait_vblank (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ramfuc_wait_vblank(struct ramfuc *ram)
{
	nvkm_memx_wait_vblank(ram->memx);
}