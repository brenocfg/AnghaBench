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
 int /*<<< orphan*/  LDT (int,unsigned long) ; 

void
alpha_write_fp_reg (unsigned long reg, unsigned long val)
{
	switch (reg) {
	      case  0: LDT( 0, val); break;
	      case  1: LDT( 1, val); break;
	      case  2: LDT( 2, val); break;
	      case  3: LDT( 3, val); break;
	      case  4: LDT( 4, val); break;
	      case  5: LDT( 5, val); break;
	      case  6: LDT( 6, val); break;
	      case  7: LDT( 7, val); break;
	      case  8: LDT( 8, val); break;
	      case  9: LDT( 9, val); break;
	      case 10: LDT(10, val); break;
	      case 11: LDT(11, val); break;
	      case 12: LDT(12, val); break;
	      case 13: LDT(13, val); break;
	      case 14: LDT(14, val); break;
	      case 15: LDT(15, val); break;
	      case 16: LDT(16, val); break;
	      case 17: LDT(17, val); break;
	      case 18: LDT(18, val); break;
	      case 19: LDT(19, val); break;
	      case 20: LDT(20, val); break;
	      case 21: LDT(21, val); break;
	      case 22: LDT(22, val); break;
	      case 23: LDT(23, val); break;
	      case 24: LDT(24, val); break;
	      case 25: LDT(25, val); break;
	      case 26: LDT(26, val); break;
	      case 27: LDT(27, val); break;
	      case 28: LDT(28, val); break;
	      case 29: LDT(29, val); break;
	      case 30: LDT(30, val); break;
	      case 31: LDT(31, val); break;
	}
}