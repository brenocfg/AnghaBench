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
typedef  int drbg_flag_t ;

/* Variables and functions */
#define  DRBG_STRENGTH128 130 
#define  DRBG_STRENGTH192 129 
#define  DRBG_STRENGTH256 128 
 int DRBG_STRENGTH_MASK ; 

__attribute__((used)) static inline unsigned short drbg_sec_strength(drbg_flag_t flags)
{
	switch (flags & DRBG_STRENGTH_MASK) {
	case DRBG_STRENGTH128:
		return 16;
	case DRBG_STRENGTH192:
		return 24;
	case DRBG_STRENGTH256:
		return 32;
	default:
		return 32;
	}
}