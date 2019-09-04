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

__attribute__((used)) static inline int
valid_bo_pre_v2 (long value)
{
  /* Certain encodings have bits that are required to be zero.
     These are (z must be zero, y may be anything):
	 0000y
	 0001y
	 001zy
	 0100y
	 0101y
	 011zy
	 1z00y
	 1z01y
	 1z1zz
  */
  if ((value & 0x14) == 0)
    return 1;
  else if ((value & 0x14) == 0x4)
    return (value & 0x2) == 0;
  else if ((value & 0x14) == 0x10)
    return (value & 0x8) == 0;
  else
    return value == 0x14;
}