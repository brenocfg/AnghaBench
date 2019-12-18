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
struct ipw_supported_rates {int /*<<< orphan*/  num_rates; scalar_t__* supported_rates; } ;

/* Variables and functions */
 scalar_t__ LIBIPW_BASIC_RATE_MASK ; 
 scalar_t__ LIBIPW_OFDM_MODULATION ; 
 scalar_t__ LIBIPW_OFDM_RATE_12MB ; 
 int LIBIPW_OFDM_RATE_12MB_MASK ; 
 scalar_t__ LIBIPW_OFDM_RATE_18MB ; 
 int LIBIPW_OFDM_RATE_18MB_MASK ; 
 scalar_t__ LIBIPW_OFDM_RATE_24MB ; 
 int LIBIPW_OFDM_RATE_24MB_MASK ; 
 scalar_t__ LIBIPW_OFDM_RATE_36MB ; 
 int LIBIPW_OFDM_RATE_36MB_MASK ; 
 scalar_t__ LIBIPW_OFDM_RATE_48MB ; 
 int LIBIPW_OFDM_RATE_48MB_MASK ; 
 scalar_t__ LIBIPW_OFDM_RATE_54MB ; 
 int LIBIPW_OFDM_RATE_54MB_MASK ; 
 scalar_t__ LIBIPW_OFDM_RATE_6MB ; 
 int LIBIPW_OFDM_RATE_6MB_MASK ; 
 scalar_t__ LIBIPW_OFDM_RATE_9MB ; 
 int LIBIPW_OFDM_RATE_9MB_MASK ; 

__attribute__((used)) static void ipw_add_ofdm_scan_rates(struct ipw_supported_rates *rates,
				    u8 modulation, u32 rate_mask)
{
	u8 basic_mask = (LIBIPW_OFDM_MODULATION == modulation) ?
	    LIBIPW_BASIC_RATE_MASK : 0;

	if (rate_mask & LIBIPW_OFDM_RATE_6MB_MASK)
		rates->supported_rates[rates->num_rates++] = basic_mask |
		    LIBIPW_OFDM_RATE_6MB;

	if (rate_mask & LIBIPW_OFDM_RATE_9MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_OFDM_RATE_9MB;

	if (rate_mask & LIBIPW_OFDM_RATE_12MB_MASK)
		rates->supported_rates[rates->num_rates++] = basic_mask |
		    LIBIPW_OFDM_RATE_12MB;

	if (rate_mask & LIBIPW_OFDM_RATE_18MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_OFDM_RATE_18MB;

	if (rate_mask & LIBIPW_OFDM_RATE_24MB_MASK)
		rates->supported_rates[rates->num_rates++] = basic_mask |
		    LIBIPW_OFDM_RATE_24MB;

	if (rate_mask & LIBIPW_OFDM_RATE_36MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_OFDM_RATE_36MB;

	if (rate_mask & LIBIPW_OFDM_RATE_48MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_OFDM_RATE_48MB;

	if (rate_mask & LIBIPW_OFDM_RATE_54MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_OFDM_RATE_54MB;
}