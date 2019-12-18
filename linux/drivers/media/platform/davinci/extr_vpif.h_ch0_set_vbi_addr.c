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
 int /*<<< orphan*/  VPIF_CH0_BTM_STRT_ADD_VANC ; 
 int /*<<< orphan*/  VPIF_CH0_TOP_STRT_ADD_VANC ; 
 int /*<<< orphan*/  regw (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ch0_set_vbi_addr(unsigned long top_vbi,
	unsigned long btm_vbi, unsigned long a, unsigned long b)
{
	regw(top_vbi, VPIF_CH0_TOP_STRT_ADD_VANC);
	regw(btm_vbi, VPIF_CH0_BTM_STRT_ADD_VANC);
}