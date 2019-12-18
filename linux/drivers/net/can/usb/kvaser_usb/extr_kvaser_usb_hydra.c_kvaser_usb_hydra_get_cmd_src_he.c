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
struct TYPE_2__ {int he_addr; int /*<<< orphan*/  transid; } ;
struct kvaser_cmd {TYPE_1__ header; } ;

/* Variables and functions */
 int KVASER_USB_HYDRA_HE_ADDR_SRC_BITS ; 
 int KVASER_USB_HYDRA_HE_ADDR_SRC_MASK ; 
 int KVASER_USB_HYDRA_TRANSID_BITS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 kvaser_usb_hydra_get_cmd_src_he(const struct kvaser_cmd *cmd)
{
	return (cmd->header.he_addr & KVASER_USB_HYDRA_HE_ADDR_SRC_MASK) >>
		KVASER_USB_HYDRA_HE_ADDR_SRC_BITS |
		le16_to_cpu(cmd->header.transid) >>
		KVASER_USB_HYDRA_TRANSID_BITS;
}