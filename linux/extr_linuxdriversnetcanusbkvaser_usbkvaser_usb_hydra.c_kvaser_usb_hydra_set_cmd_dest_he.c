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
struct TYPE_2__ {int he_addr; } ;
struct kvaser_cmd {TYPE_1__ header; } ;

/* Variables and functions */
 int KVASER_USB_HYDRA_HE_ADDR_DEST_MASK ; 
 int KVASER_USB_HYDRA_HE_ADDR_SRC_MASK ; 

__attribute__((used)) static inline void kvaser_usb_hydra_set_cmd_dest_he(struct kvaser_cmd *cmd,
						    u8 dest_he)
{
	cmd->header.he_addr =
		(cmd->header.he_addr & KVASER_USB_HYDRA_HE_ADDR_SRC_MASK) |
		(dest_he & KVASER_USB_HYDRA_HE_ADDR_DEST_MASK);
}