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

/* Variables and functions */
 int LVDPLLCR_CEEN ; 
 int LVDPLLCR_COSEL ; 
 int LVDPLLCR_PLLDLYCNT_121M ; 
 int LVDPLLCR_PLLDLYCNT_150M ; 
 int LVDPLLCR_PLLDLYCNT_38M ; 
 int LVDPLLCR_PLLDLYCNT_60M ; 

__attribute__((used)) static u32 rcar_lvds_lvdpllcr_gen2(unsigned int freq)
{
	if (freq < 39000)
		return LVDPLLCR_CEEN | LVDPLLCR_COSEL | LVDPLLCR_PLLDLYCNT_38M;
	else if (freq < 61000)
		return LVDPLLCR_CEEN | LVDPLLCR_COSEL | LVDPLLCR_PLLDLYCNT_60M;
	else if (freq < 121000)
		return LVDPLLCR_CEEN | LVDPLLCR_COSEL | LVDPLLCR_PLLDLYCNT_121M;
	else
		return LVDPLLCR_PLLDLYCNT_150M;
}