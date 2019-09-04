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

/* Variables and functions */
 int SIO_REG_LDSEL ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static inline void
superio_select(int base, int ld)
{
	outb(SIO_REG_LDSEL, base);
	outb(ld, base + 1);
}