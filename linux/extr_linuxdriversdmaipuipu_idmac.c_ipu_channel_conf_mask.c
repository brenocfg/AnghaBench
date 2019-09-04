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
typedef  enum ipu_channel { ____Placeholder_ipu_channel } ipu_channel ;

/* Variables and functions */
#define  IDMAC_IC_0 131 
#define  IDMAC_IC_7 130 
#define  IDMAC_SDC_0 129 
#define  IDMAC_SDC_1 128 
 int IPU_CONF_CSI_EN ; 
 int IPU_CONF_DI_EN ; 
 int IPU_CONF_IC_EN ; 
 int IPU_CONF_SDC_EN ; 

__attribute__((used)) static uint32_t ipu_channel_conf_mask(enum ipu_channel channel)
{
	uint32_t mask;

	switch (channel) {
	case IDMAC_IC_0:
	case IDMAC_IC_7:
		mask = IPU_CONF_CSI_EN | IPU_CONF_IC_EN;
		break;
	case IDMAC_SDC_0:
	case IDMAC_SDC_1:
		mask = IPU_CONF_SDC_EN | IPU_CONF_DI_EN;
		break;
	default:
		mask = 0;
		break;
	}

	return mask;
}