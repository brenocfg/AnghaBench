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
typedef  int u32 ;
struct nes_cm_core {int mtu; int free_tx_pkt_max; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NES_CM_SET_FREE_PKT_Q_SIZE 129 
#define  NES_CM_SET_PKT_SIZE 128 

__attribute__((used)) static int mini_cm_set(struct nes_cm_core *cm_core, u32 type, u32 value)
{
	int ret = 0;

	switch (type) {
	case NES_CM_SET_PKT_SIZE:
		cm_core->mtu = value;
		break;
	case NES_CM_SET_FREE_PKT_Q_SIZE:
		cm_core->free_tx_pkt_max = value;
		break;
	default:
		/* unknown set option */
		ret = -EINVAL;
	}

	return ret;
}