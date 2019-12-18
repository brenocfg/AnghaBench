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
typedef  int /*<<< orphan*/  u16 ;
struct perm_bits {int /*<<< orphan*/ * write; int /*<<< orphan*/ * virt; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void p_setw(struct perm_bits *p, int off, u16 virt, u16 write)
{
	*(__le16 *)(&p->virt[off]) = cpu_to_le16(virt);
	*(__le16 *)(&p->write[off]) = cpu_to_le16(write);
}