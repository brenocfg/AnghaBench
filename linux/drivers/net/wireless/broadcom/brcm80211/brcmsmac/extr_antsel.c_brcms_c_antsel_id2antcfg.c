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
typedef  int u8 ;
struct antsel_info {scalar_t__ antsel_type; } ;

/* Variables and functions */
 scalar_t__ ANTSEL_2x3 ; 
 scalar_t__ ANTSEL_2x4 ; 
 int ANT_SELCFG_DEF_2x2 ; 

__attribute__((used)) static u8 brcms_c_antsel_id2antcfg(struct antsel_info *asi, u8 id)
{
	u8 antcfg = ANT_SELCFG_DEF_2x2;

	if (asi->antsel_type == ANTSEL_2x4) {
		/* 2x4 antenna diversity board, 4 cfgs: 0-2 0-3 1-2 1-3 */
		antcfg = (((id & 0x2) << 3) | ((id & 0x1) + 2));
		return antcfg;

	} else if (asi->antsel_type == ANTSEL_2x3) {
		/* 2x3 antenna selection, 3 cfgs: 0-1 0-2 2-1 */
		antcfg = (((id & 0x02) << 4) | ((id & 0x1) + 1));
		return antcfg;
	}

	return antcfg;
}