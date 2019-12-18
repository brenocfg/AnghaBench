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
 int SOC15_IH_CLIENTID_SDMA0 ; 
 int SOC15_IH_CLIENTID_SDMA1 ; 
 int SOC15_IH_CLIENTID_SDMA2 ; 
 int SOC15_IH_CLIENTID_SDMA3 ; 
 int SOC15_IH_CLIENTID_SDMA4 ; 
 int SOC15_IH_CLIENTID_SDMA5 ; 
 int SOC15_IH_CLIENTID_SDMA6 ; 
 int SOC15_IH_CLIENTID_SDMA7 ; 

__attribute__((used)) static unsigned sdma_v4_0_seq_to_irq_id(int seq_num)
{
	switch (seq_num) {
	case 0:
		return SOC15_IH_CLIENTID_SDMA0;
	case 1:
		return SOC15_IH_CLIENTID_SDMA1;
	case 2:
		return SOC15_IH_CLIENTID_SDMA2;
	case 3:
		return SOC15_IH_CLIENTID_SDMA3;
	case 4:
		return SOC15_IH_CLIENTID_SDMA4;
	case 5:
		return SOC15_IH_CLIENTID_SDMA5;
	case 6:
		return SOC15_IH_CLIENTID_SDMA6;
	case 7:
		return SOC15_IH_CLIENTID_SDMA7;
	default:
		break;
	}
	return -EINVAL;
}