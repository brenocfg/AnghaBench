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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum brcmu_chan_bw { ____Placeholder_brcmu_chan_bw } brcmu_chan_bw ;

/* Variables and functions */
#define  BRCMU_CHAN_BW_20 129 
#define  BRCMU_CHAN_BW_40 128 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11N_BW_20 ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11N_BW_40 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static u16 d11n_bw(enum brcmu_chan_bw bw)
{
	switch (bw) {
	case BRCMU_CHAN_BW_20:
		return BRCMU_CHSPEC_D11N_BW_20;
	case BRCMU_CHAN_BW_40:
		return BRCMU_CHSPEC_D11N_BW_40;
	default:
		WARN_ON(1);
	}
	return 0;
}