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
 int /*<<< orphan*/  HGA_INDEX_PORT ; 
 int /*<<< orphan*/  HGA_VALUE_PORT ; 
 unsigned char inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int test_hga_b(unsigned char val, unsigned char reg)
{
	outb_p(reg, HGA_INDEX_PORT); 
	outb  (val, HGA_VALUE_PORT);
	udelay(20); val = (inb_p(HGA_VALUE_PORT) == val);
	return val;
}