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

__attribute__((used)) static inline uint32_t __offset_WB(uint32_t idx)
{
	switch (idx) {
#if 0  /* TEMPORARY until patch that adds wb.base[] is merged */
		case 0: return (mdp5_cfg->wb.base[0]);
		case 1: return (mdp5_cfg->wb.base[1]);
		case 2: return (mdp5_cfg->wb.base[2]);
		case 3: return (mdp5_cfg->wb.base[3]);
		case 4: return (mdp5_cfg->wb.base[4]);
#endif
		default: return INVALID_IDX(idx);
	}
}