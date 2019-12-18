#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int* base; } ;
struct TYPE_4__ {TYPE_1__ lm; } ;

/* Variables and functions */
 int INVALID_IDX (int) ; 
 TYPE_2__* mdp5_cfg ; 

__attribute__((used)) static inline uint32_t __offset_LM(uint32_t idx)
{
	switch (idx) {
		case 0: return (mdp5_cfg->lm.base[0]);
		case 1: return (mdp5_cfg->lm.base[1]);
		case 2: return (mdp5_cfg->lm.base[2]);
		case 3: return (mdp5_cfg->lm.base[3]);
		case 4: return (mdp5_cfg->lm.base[4]);
		case 5: return (mdp5_cfg->lm.base[5]);
		default: return INVALID_IDX(idx);
	}
}