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
typedef  void* u8 ;
struct perm_bits {void** write; void** virt; } ;

/* Variables and functions */

__attribute__((used)) static inline void p_setb(struct perm_bits *p, int off, u8 virt, u8 write)
{
	p->virt[off] = virt;
	p->write[off] = write;
}