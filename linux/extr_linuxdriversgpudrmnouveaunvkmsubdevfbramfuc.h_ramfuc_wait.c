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
typedef  int /*<<< orphan*/  u32 ;
struct ramfuc {int /*<<< orphan*/  memx; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_memx_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ramfuc_wait(struct ramfuc *ram, u32 addr, u32 mask, u32 data, u32 nsec)
{
	nvkm_memx_wait(ram->memx, addr, mask, data, nsec);
}