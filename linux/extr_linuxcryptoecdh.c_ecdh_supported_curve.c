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
#define  ECC_CURVE_NIST_P192 129 
 unsigned int ECC_CURVE_NIST_P192_DIGITS ; 
#define  ECC_CURVE_NIST_P256 128 
 unsigned int ECC_CURVE_NIST_P256_DIGITS ; 

__attribute__((used)) static unsigned int ecdh_supported_curve(unsigned int curve_id)
{
	switch (curve_id) {
	case ECC_CURVE_NIST_P192: return ECC_CURVE_NIST_P192_DIGITS;
	case ECC_CURVE_NIST_P256: return ECC_CURVE_NIST_P256_DIGITS;
	default: return 0;
	}
}