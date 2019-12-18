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
typedef  enum mdp5_igc_type { ____Placeholder_mdp5_igc_type } mdp5_igc_type ;

/* Variables and functions */
#define  IGC_DMA 131 
#define  IGC_DSPP 130 
#define  IGC_RGB 129 
#define  IGC_VIG 128 
 int INVALID_IDX (int) ; 

__attribute__((used)) static inline uint32_t __offset_IGC(enum mdp5_igc_type idx)
{
	switch (idx) {
		case IGC_VIG: return 0x00000200;
		case IGC_RGB: return 0x00000210;
		case IGC_DMA: return 0x00000220;
		case IGC_DSPP: return 0x00000300;
		default: return INVALID_IDX(idx);
	}
}