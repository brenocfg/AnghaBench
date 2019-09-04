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
typedef  int u32 ;
struct TYPE_2__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct hfi_sys_test_ssr_pkt {int trigger_type; TYPE_1__ hdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_CMD_SYS_TEST_SSR ; 
#define  HFI_TEST_SSR_HW_WDOG_IRQ 130 
#define  HFI_TEST_SSR_SW_DIV_BY_ZERO 129 
#define  HFI_TEST_SSR_SW_ERR_FATAL 128 

int pkt_sys_ssr_cmd(struct hfi_sys_test_ssr_pkt *pkt, u32 trigger_type)
{
	switch (trigger_type) {
	case HFI_TEST_SSR_SW_ERR_FATAL:
	case HFI_TEST_SSR_SW_DIV_BY_ZERO:
	case HFI_TEST_SSR_HW_WDOG_IRQ:
		break;
	default:
		return -EINVAL;
	}

	pkt->hdr.size = sizeof(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_TEST_SSR;
	pkt->trigger_type = trigger_type;

	return 0;
}