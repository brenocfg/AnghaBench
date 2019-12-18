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
typedef  enum dc_link_rate { ____Placeholder_dc_link_rate } dc_link_rate ;

/* Variables and functions */
 int LINK_RATE_HIGH ; 
 int LINK_RATE_HIGH2 ; 
 int LINK_RATE_HIGH3 ; 
 int LINK_RATE_LOW ; 
 int LINK_RATE_RATE_2 ; 
 int LINK_RATE_RATE_3 ; 
 int LINK_RATE_RATE_6 ; 
 int LINK_RATE_RBR2 ; 
 int LINK_RATE_UNKNOWN ; 

enum dc_link_rate linkRateInKHzToLinkRateMultiplier(uint32_t link_rate_in_khz)
{
	enum dc_link_rate link_rate;
	// LinkRate is normally stored as a multiplier of 0.27 Gbps per lane. Do the translation.
	switch (link_rate_in_khz) {
	case 1620000:
		link_rate = LINK_RATE_LOW;		// Rate_1 (RBR)		- 1.62 Gbps/Lane
		break;
	case 2160000:
		link_rate = LINK_RATE_RATE_2;	// Rate_2			- 2.16 Gbps/Lane
		break;
	case 2430000:
		link_rate = LINK_RATE_RATE_3;	// Rate_3			- 2.43 Gbps/Lane
		break;
	case 2700000:
		link_rate = LINK_RATE_HIGH;		// Rate_4 (HBR)		- 2.70 Gbps/Lane
		break;
	case 3240000:
		link_rate = LINK_RATE_RBR2;		// Rate_5 (RBR2)	- 3.24 Gbps/Lane
		break;
	case 4320000:
		link_rate = LINK_RATE_RATE_6;	// Rate_6			- 4.32 Gbps/Lane
		break;
	case 5400000:
		link_rate = LINK_RATE_HIGH2;	// Rate_7 (HBR2)	- 5.40 Gbps/Lane
		break;
	case 8100000:
		link_rate = LINK_RATE_HIGH3;	// Rate_8 (HBR3)	- 8.10 Gbps/Lane
		break;
	default:
		link_rate = LINK_RATE_UNKNOWN;
		break;
	}
	return link_rate;
}