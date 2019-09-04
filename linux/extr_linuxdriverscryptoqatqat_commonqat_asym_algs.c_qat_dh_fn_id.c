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
 unsigned long PKE_DH_1536 ; 
 unsigned long PKE_DH_2048 ; 
 unsigned long PKE_DH_3072 ; 
 unsigned long PKE_DH_4096 ; 
 unsigned long PKE_DH_G2_1536 ; 
 unsigned long PKE_DH_G2_2048 ; 
 unsigned long PKE_DH_G2_3072 ; 
 unsigned long PKE_DH_G2_4096 ; 

__attribute__((used)) static unsigned long qat_dh_fn_id(unsigned int len, bool g2)
{
	unsigned int bitslen = len << 3;

	switch (bitslen) {
	case 1536:
		return g2 ? PKE_DH_G2_1536 : PKE_DH_1536;
	case 2048:
		return g2 ? PKE_DH_G2_2048 : PKE_DH_2048;
	case 3072:
		return g2 ? PKE_DH_G2_3072 : PKE_DH_3072;
	case 4096:
		return g2 ? PKE_DH_G2_4096 : PKE_DH_4096;
	default:
		return 0;
	};
}