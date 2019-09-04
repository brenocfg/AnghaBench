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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u16
cellrate_to_float(u32 cr)
{

#define	NZ 		0x4000
#define	M_BITS		9		/* Number of bits in mantissa */
#define	E_BITS		5		/* Number of bits in exponent */
#define	M_MASK		0x1ff		
#define	E_MASK		0x1f
  u16   flot;
  u32	tmp = cr & 0x00ffffff;
  int 	i   = 0;
  if (cr == 0)
     return 0;
  while (tmp != 1) {
     tmp >>= 1;
     i++;
  }
  if (i == M_BITS)
     flot = NZ | (i << M_BITS) | (cr & M_MASK);
  else if (i < M_BITS)
     flot = NZ | (i << M_BITS) | ((cr << (M_BITS - i)) & M_MASK);
  else
     flot = NZ | (i << M_BITS) | ((cr >> (i - M_BITS)) & M_MASK);
  return flot;
}