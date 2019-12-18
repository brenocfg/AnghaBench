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
typedef  int u64 ;
struct niu {int port; } ;

/* Variables and functions */
 int ESR_INT_DET0_P0 ; 
 int ESR_INT_DET0_P1 ; 
 int /*<<< orphan*/  ESR_INT_SIGNALS ; 
 int ESR_INT_SIGNALS_P0_BITS ; 
 int ESR_INT_SIGNALS_P1_BITS ; 
 int ESR_INT_SRDY0_P0 ; 
 int ESR_INT_SRDY0_P1 ; 
 int ESR_INT_XDP_P0_CH0 ; 
 int ESR_INT_XDP_P0_CH1 ; 
 int ESR_INT_XDP_P0_CH2 ; 
 int ESR_INT_XDP_P0_CH3 ; 
 int ESR_INT_XDP_P1_CH0 ; 
 int ESR_INT_XDP_P1_CH1 ; 
 int ESR_INT_XDP_P1_CH2 ; 
 int ESR_INT_XDP_P1_CH3 ; 
 int ESR_INT_XSRDY_P0 ; 
 int ESR_INT_XSRDY_P1 ; 
 int nr64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_10g_phy_present(struct niu *np)
{
	u64 sig, mask, val;

	sig = nr64(ESR_INT_SIGNALS);
	switch (np->port) {
	case 0:
		mask = ESR_INT_SIGNALS_P0_BITS;
		val = (ESR_INT_SRDY0_P0 |
		       ESR_INT_DET0_P0 |
		       ESR_INT_XSRDY_P0 |
		       ESR_INT_XDP_P0_CH3 |
		       ESR_INT_XDP_P0_CH2 |
		       ESR_INT_XDP_P0_CH1 |
		       ESR_INT_XDP_P0_CH0);
		break;

	case 1:
		mask = ESR_INT_SIGNALS_P1_BITS;
		val = (ESR_INT_SRDY0_P1 |
		       ESR_INT_DET0_P1 |
		       ESR_INT_XSRDY_P1 |
		       ESR_INT_XDP_P1_CH3 |
		       ESR_INT_XDP_P1_CH2 |
		       ESR_INT_XDP_P1_CH1 |
		       ESR_INT_XDP_P1_CH0);
		break;

	default:
		return 0;
	}

	if ((sig & mask) != val)
		return 0;
	return 1;
}