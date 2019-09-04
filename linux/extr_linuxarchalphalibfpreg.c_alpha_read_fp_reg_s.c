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
 int /*<<< orphan*/  STS (int,unsigned long) ; 

unsigned long
alpha_read_fp_reg_s (unsigned long reg)
{
	unsigned long val;

	switch (reg) {
	      case  0: STS( 0, val); break;
	      case  1: STS( 1, val); break;
	      case  2: STS( 2, val); break;
	      case  3: STS( 3, val); break;
	      case  4: STS( 4, val); break;
	      case  5: STS( 5, val); break;
	      case  6: STS( 6, val); break;
	      case  7: STS( 7, val); break;
	      case  8: STS( 8, val); break;
	      case  9: STS( 9, val); break;
	      case 10: STS(10, val); break;
	      case 11: STS(11, val); break;
	      case 12: STS(12, val); break;
	      case 13: STS(13, val); break;
	      case 14: STS(14, val); break;
	      case 15: STS(15, val); break;
	      case 16: STS(16, val); break;
	      case 17: STS(17, val); break;
	      case 18: STS(18, val); break;
	      case 19: STS(19, val); break;
	      case 20: STS(20, val); break;
	      case 21: STS(21, val); break;
	      case 22: STS(22, val); break;
	      case 23: STS(23, val); break;
	      case 24: STS(24, val); break;
	      case 25: STS(25, val); break;
	      case 26: STS(26, val); break;
	      case 27: STS(27, val); break;
	      case 28: STS(28, val); break;
	      case 29: STS(29, val); break;
	      case 30: STS(30, val); break;
	      case 31: STS(31, val); break;
	      default: return 0;
	}
	return val;
}