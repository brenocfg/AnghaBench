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
 int /*<<< orphan*/  VPIF_CH3_BTM_STRT_ADD_CHROMA ; 
 int /*<<< orphan*/  VPIF_CH3_BTM_STRT_ADD_LUMA ; 
 int /*<<< orphan*/  VPIF_CH3_TOP_STRT_ADD_CHROMA ; 
 int /*<<< orphan*/  VPIF_CH3_TOP_STRT_ADD_LUMA ; 
 int /*<<< orphan*/  regw (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ch3_set_videobuf_addr(unsigned long top_strt_luma,
					 unsigned long btm_strt_luma,
					 unsigned long top_strt_chroma,
					 unsigned long btm_strt_chroma)
{
	regw(top_strt_luma, VPIF_CH3_TOP_STRT_ADD_LUMA);
	regw(btm_strt_luma, VPIF_CH3_BTM_STRT_ADD_LUMA);
	regw(top_strt_chroma, VPIF_CH3_TOP_STRT_ADD_CHROMA);
	regw(btm_strt_chroma, VPIF_CH3_BTM_STRT_ADD_CHROMA);
}