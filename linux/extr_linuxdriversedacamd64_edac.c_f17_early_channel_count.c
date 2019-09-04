#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct amd64_pvt {TYPE_1__* umc; } ;
struct TYPE_2__ {int sdp_ctrl; } ;

/* Variables and functions */
 int NUM_UMCS ; 
 int UMC_SDP_INIT ; 
 int /*<<< orphan*/  amd64_info (char*,int) ; 

__attribute__((used)) static int f17_early_channel_count(struct amd64_pvt *pvt)
{
	int i, channels = 0;

	/* SDP Control bit 31 (SdpInit) is clear for unused UMC channels */
	for (i = 0; i < NUM_UMCS; i++)
		channels += !!(pvt->umc[i].sdp_ctrl & UMC_SDP_INIT);

	amd64_info("MCT channel count: %d\n", channels);

	return channels;
}