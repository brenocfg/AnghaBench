#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
#define  MB4H_A9WDOG_CONF 136 
#define  MB4H_A9WDOG_DIS 135 
#define  MB4H_A9WDOG_EN 134 
#define  MB4H_A9WDOG_KICK 133 
#define  MB4H_A9WDOG_LOAD 132 
#define  MB4H_HOTDOG 131 
#define  MB4H_HOTMON 130 
#define  MB4H_HOT_PERIOD 129 
#define  MB4H_MEM_ST 128 
 int /*<<< orphan*/  MBOX_BIT (int) ; 
 int /*<<< orphan*/  PRCM_ARM_IT1_CLR ; 
 scalar_t__ PRCM_MBOX_HEADER_REQ_MB4 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_1__ mb4_transfer ; 
 int /*<<< orphan*/  print_unknown_header_warning (int,int) ; 
 int readb (scalar_t__) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool read_mailbox_4(void)
{
	u8 header;
	bool do_complete = true;

	header = readb(tcdm_base + PRCM_MBOX_HEADER_REQ_MB4);
	switch (header) {
	case MB4H_MEM_ST:
	case MB4H_HOTDOG:
	case MB4H_HOTMON:
	case MB4H_HOT_PERIOD:
	case MB4H_A9WDOG_CONF:
	case MB4H_A9WDOG_EN:
	case MB4H_A9WDOG_DIS:
	case MB4H_A9WDOG_LOAD:
	case MB4H_A9WDOG_KICK:
		break;
	default:
		print_unknown_header_warning(4, header);
		do_complete = false;
		break;
	}

	writel(MBOX_BIT(4), PRCM_ARM_IT1_CLR);

	if (do_complete)
		complete(&mb4_transfer.work);

	return false;
}