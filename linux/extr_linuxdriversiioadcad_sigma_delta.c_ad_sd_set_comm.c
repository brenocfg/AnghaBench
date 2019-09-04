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
typedef  int uint8_t ;
struct ad_sigma_delta {int comm; } ;

/* Variables and functions */
 int AD_SD_COMM_CHAN_MASK ; 

void ad_sd_set_comm(struct ad_sigma_delta *sigma_delta, uint8_t comm)
{
	/* Some variants use the lower two bits of the communications register
	 * to select the channel */
	sigma_delta->comm = comm & AD_SD_COMM_CHAN_MASK;
}