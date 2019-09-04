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
typedef  int uint32_t ;
struct dc_link_settings {int link_rate; int lane_count; } ;

/* Variables and functions */
 int LINK_RATE_REF_FREQ_IN_KHZ ; 

__attribute__((used)) static uint32_t bandwidth_in_kbps_from_link_settings(
	const struct dc_link_settings *link_setting)
{
	uint32_t link_rate_in_kbps = link_setting->link_rate *
		LINK_RATE_REF_FREQ_IN_KHZ;

	uint32_t lane_count  = link_setting->lane_count;
	uint32_t kbps = link_rate_in_kbps;

	kbps *= lane_count;
	kbps *= 8;   /* 8 bits per byte*/

	return kbps;

}