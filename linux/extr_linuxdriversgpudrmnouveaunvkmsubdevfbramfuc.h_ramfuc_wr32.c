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
struct ramfuc_reg {unsigned int mask; scalar_t__ stride; int /*<<< orphan*/  data; scalar_t__ addr; int /*<<< orphan*/  sequence; } ;
struct ramfuc {int /*<<< orphan*/  memx; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_memx_wr32 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ramfuc_wr32(struct ramfuc *ram, struct ramfuc_reg *reg, u32 data)
{
	unsigned int mask, off = 0;

	reg->sequence = ram->sequence;
	reg->data = data;

	for (mask = reg->mask; mask > 0; mask = (mask & ~1) >> 1) {
		if (mask & 1)
			nvkm_memx_wr32(ram->memx, reg->addr+off, reg->data);
		off += reg->stride;
	}
}