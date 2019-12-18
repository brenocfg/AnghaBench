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
typedef  enum mdp_component_type { ____Placeholder_mdp_component_type } mdp_component_type ;

/* Variables and functions */
#define  COMP_0 130 
#define  COMP_1_2 129 
#define  COMP_3 128 
 int INVALID_IDX (int) ; 

__attribute__((used)) static inline uint32_t __offset_SW_PIX_EXT(enum mdp_component_type idx)
{
	switch (idx) {
		case COMP_0: return 0x00000100;
		case COMP_1_2: return 0x00000110;
		case COMP_3: return 0x00000120;
		default: return INVALID_IDX(idx);
	}
}