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
struct r8152 {int rx_buf_sz; int version; TYPE_1__* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_TYPE_USB ; 
#define  RTL_VER_03 133 
#define  RTL_VER_04 132 
#define  RTL_VER_05 131 
#define  RTL_VER_06 130 
#define  RTL_VER_08 129 
#define  RTL_VER_09 128 
 int /*<<< orphan*/  USB_RX_EARLY_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rx_reserved_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8153_set_rx_early_size(struct r8152 *tp)
{
	u32 ocp_data = tp->rx_buf_sz - rx_reserved_size(tp->netdev->mtu);

	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EARLY_SIZE,
			       ocp_data / 4);
		break;
	case RTL_VER_08:
	case RTL_VER_09:
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EARLY_SIZE,
			       ocp_data / 8);
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}
}