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
 unsigned int ETH_HLEN ; 
 unsigned int macsec_sectag_len (int) ; 

__attribute__((used)) static unsigned int macsec_hdr_len(bool sci_present)
{
	return macsec_sectag_len(sci_present) + ETH_HLEN;
}