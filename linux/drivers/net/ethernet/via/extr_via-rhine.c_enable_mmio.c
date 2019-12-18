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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ ConfigA ; 
 scalar_t__ ConfigD ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int rqNeedEnMMIO ; 
 int rqRhineI ; 

__attribute__((used)) static void enable_mmio(long pioaddr, u32 quirks)
{
	int n;

	if (quirks & rqNeedEnMMIO) {
		if (quirks & rqRhineI) {
			/* More recent docs say that this bit is reserved */
			n = inb(pioaddr + ConfigA) | 0x20;
			outb(n, pioaddr + ConfigA);
		} else {
			n = inb(pioaddr + ConfigD) | 0x80;
			outb(n, pioaddr + ConfigD);
		}
	}
}