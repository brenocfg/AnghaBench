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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ cmd640_key ; 
 int /*<<< orphan*/  inb_p (scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 

__attribute__((used)) static u8 get_cmd640_reg_pci2(u16 reg)
{
	u8 b;

	outb_p(0x10, 0xcf8);
	b = inb_p(cmd640_key + reg);
	outb_p(0, 0xcf8);
	return b;
}