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
 int EINVAL ; 
#define  SOC15_IH_CLIENTID_SDMA0 135 
#define  SOC15_IH_CLIENTID_SDMA1 134 
#define  SOC15_IH_CLIENTID_SDMA2 133 
#define  SOC15_IH_CLIENTID_SDMA3 132 
#define  SOC15_IH_CLIENTID_SDMA4 131 
#define  SOC15_IH_CLIENTID_SDMA5 130 
#define  SOC15_IH_CLIENTID_SDMA6 129 
#define  SOC15_IH_CLIENTID_SDMA7 128 

__attribute__((used)) static int sdma_v4_0_irq_id_to_seq(unsigned client_id)
{
	switch (client_id) {
	case SOC15_IH_CLIENTID_SDMA0:
		return 0;
	case SOC15_IH_CLIENTID_SDMA1:
		return 1;
	case SOC15_IH_CLIENTID_SDMA2:
		return 2;
	case SOC15_IH_CLIENTID_SDMA3:
		return 3;
	case SOC15_IH_CLIENTID_SDMA4:
		return 4;
	case SOC15_IH_CLIENTID_SDMA5:
		return 5;
	case SOC15_IH_CLIENTID_SDMA6:
		return 6;
	case SOC15_IH_CLIENTID_SDMA7:
		return 7;
	default:
		break;
	}
	return -EINVAL;
}