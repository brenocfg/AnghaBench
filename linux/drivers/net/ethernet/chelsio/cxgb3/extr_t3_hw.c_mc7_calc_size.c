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
 int F_BKS ; 
 int F_ORG ; 
 unsigned int G_DEN (int) ; 
 unsigned int G_WIDTH (int) ; 

__attribute__((used)) static unsigned int mc7_calc_size(u32 cfg)
{
	unsigned int width = G_WIDTH(cfg);
	unsigned int banks = !!(cfg & F_BKS) + 1;
	unsigned int org = !!(cfg & F_ORG) + 1;
	unsigned int density = G_DEN(cfg);
	unsigned int MBs = ((256 << density) * banks) / (org << width);

	return MBs << 20;
}