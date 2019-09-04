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
typedef  int u16 ;
struct ixgbe_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
#define  IXGBE_PCIDEVCTRL2_16_32ms 136 
#define  IXGBE_PCIDEVCTRL2_16_32ms_def 135 
#define  IXGBE_PCIDEVCTRL2_17_34s 134 
#define  IXGBE_PCIDEVCTRL2_1_2ms 133 
#define  IXGBE_PCIDEVCTRL2_1_2s 132 
#define  IXGBE_PCIDEVCTRL2_260_520ms 131 
#define  IXGBE_PCIDEVCTRL2_4_8s 130 
#define  IXGBE_PCIDEVCTRL2_50_100us 129 
#define  IXGBE_PCIDEVCTRL2_65_130ms 128 
 int IXGBE_PCIDEVCTRL2_TIMEO_MASK ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int /*<<< orphan*/  pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned long ixgbe_get_completion_timeout(struct ixgbe_adapter *adapter)
{
	u16 devctl2;

	pcie_capability_read_word(adapter->pdev, PCI_EXP_DEVCTL2, &devctl2);

	switch (devctl2 & IXGBE_PCIDEVCTRL2_TIMEO_MASK) {
	case IXGBE_PCIDEVCTRL2_17_34s:
	case IXGBE_PCIDEVCTRL2_4_8s:
		/* For now we cap the upper limit on delay to 2 seconds
		 * as we end up going up to 34 seconds of delay in worst
		 * case timeout value.
		 */
	case IXGBE_PCIDEVCTRL2_1_2s:
		return 2000000ul;	/* 2.0 s */
	case IXGBE_PCIDEVCTRL2_260_520ms:
		return 520000ul;	/* 520 ms */
	case IXGBE_PCIDEVCTRL2_65_130ms:
		return 130000ul;	/* 130 ms */
	case IXGBE_PCIDEVCTRL2_16_32ms:
		return 32000ul;		/* 32 ms */
	case IXGBE_PCIDEVCTRL2_1_2ms:
		return 2000ul;		/* 2 ms */
	case IXGBE_PCIDEVCTRL2_50_100us:
		return 100ul;		/* 100 us */
	case IXGBE_PCIDEVCTRL2_16_32ms_def:
		return 32000ul;		/* 32 ms */
	default:
		break;
	}

	/* We shouldn't need to hit this path, but just in case default as
	 * though completion timeout is not supported and support 32ms.
	 */
	return 32000ul;
}