#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
struct idt_data {int /*<<< orphan*/  bits; scalar_t__ segment; scalar_t__ addr; } ;
struct TYPE_3__ {void* offset_middle; int /*<<< orphan*/  bits; void* segment; void* offset_low; } ;
typedef  TYPE_1__ gate_desc ;

/* Variables and functions */

__attribute__((used)) static inline void idt_init_desc(gate_desc *gate, const struct idt_data *d)
{
	unsigned long addr = (unsigned long) d->addr;

	gate->offset_low	= (u16) addr;
	gate->segment		= (u16) d->segment;
	gate->bits		= d->bits;
	gate->offset_middle	= (u16) (addr >> 16);
#ifdef CONFIG_X86_64
	gate->offset_high	= (u32) (addr >> 32);
	gate->reserved		= 0;
#endif
}