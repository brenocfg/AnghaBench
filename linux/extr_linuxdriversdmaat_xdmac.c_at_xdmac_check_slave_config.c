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
struct dma_slave_config {scalar_t__ src_maxburst; scalar_t__ dst_maxburst; scalar_t__ src_addr_width; scalar_t__ dst_addr_width; } ;

/* Variables and functions */
 scalar_t__ AT_XDMAC_MAX_CSIZE ; 
 scalar_t__ AT_XDMAC_MAX_DWIDTH ; 
 int EINVAL ; 

__attribute__((used)) static int at_xdmac_check_slave_config(struct dma_slave_config *sconfig)
{
	if ((sconfig->src_maxburst > AT_XDMAC_MAX_CSIZE)
	    || (sconfig->dst_maxburst > AT_XDMAC_MAX_CSIZE))
		return -EINVAL;

	if ((sconfig->src_addr_width > AT_XDMAC_MAX_DWIDTH)
	    || (sconfig->dst_addr_width > AT_XDMAC_MAX_DWIDTH))
		return -EINVAL;

	return 0;
}