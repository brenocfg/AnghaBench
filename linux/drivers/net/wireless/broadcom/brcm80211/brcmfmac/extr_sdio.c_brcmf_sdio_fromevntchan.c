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
typedef  scalar_t__ u8 ;
typedef  int u32 ;

/* Variables and functions */
 int SDPCM_CHANNEL_MASK ; 
 int SDPCM_CHANNEL_SHIFT ; 
 scalar_t__ SDPCM_EVENT_CHANNEL ; 

__attribute__((used)) static inline bool brcmf_sdio_fromevntchan(u8 *swheader)
{
	u32 hdrvalue;
	u8 ret;

	hdrvalue = *(u32 *)swheader;
	ret = (u8)((hdrvalue & SDPCM_CHANNEL_MASK) >> SDPCM_CHANNEL_SHIFT);

	return (ret == SDPCM_EVENT_CHANNEL);
}