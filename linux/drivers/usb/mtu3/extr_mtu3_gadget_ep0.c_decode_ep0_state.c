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
struct mtu3 {int ep0_state; } ;

/* Variables and functions */
#define  MU3D_EP0_STATE_RX 132 
#define  MU3D_EP0_STATE_SETUP 131 
#define  MU3D_EP0_STATE_STALL 130 
#define  MU3D_EP0_STATE_TX 129 
#define  MU3D_EP0_STATE_TX_END 128 

__attribute__((used)) static char *decode_ep0_state(struct mtu3 *mtu)
{
	switch (mtu->ep0_state) {
	case MU3D_EP0_STATE_SETUP:
		return "SETUP";
	case MU3D_EP0_STATE_TX:
		return "IN";
	case MU3D_EP0_STATE_RX:
		return "OUT";
	case MU3D_EP0_STATE_TX_END:
		return "TX-END";
	case MU3D_EP0_STATE_STALL:
		return "STALL";
	default:
		return "??";
	}
}