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
typedef  int uint32_t ;

/* Variables and functions */
 int INVALID_IDX (int) ; 

__attribute__((used)) static inline uint32_t __offset_LAYER_EXT(uint32_t idx)
{
	switch (idx) {
		case 0: return 0x00000040;
		case 1: return 0x00000044;
		case 2: return 0x00000048;
		case 3: return 0x0000004c;
		case 4: return 0x00000050;
		case 5: return 0x00000054;
		default: return INVALID_IDX(idx);
	}
}