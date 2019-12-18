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
struct dp_sdp_header {int /*<<< orphan*/  HB2; int /*<<< orphan*/  HB1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_SDP_PPS ; 
 int /*<<< orphan*/  DP_SDP_PPS_HEADER_PAYLOAD_BYTES_MINUS_1 ; 
 int /*<<< orphan*/  memset (struct dp_sdp_header*,int /*<<< orphan*/ ,int) ; 

void drm_dsc_dp_pps_header_init(struct dp_sdp_header *pps_header)
{
	memset(pps_header, 0, sizeof(*pps_header));

	pps_header->HB1 = DP_SDP_PPS;
	pps_header->HB2 = DP_SDP_PPS_HEADER_PAYLOAD_BYTES_MINUS_1;
}