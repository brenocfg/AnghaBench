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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  transid; } ;
struct kvaser_cmd {TYPE_1__ header; } ;

/* Variables and functions */
 int KVASER_USB_HYDRA_TRANSID_MASK ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 kvaser_usb_hydra_get_cmd_transid(const struct kvaser_cmd *cmd)
{
	return le16_to_cpu(cmd->header.transid) & KVASER_USB_HYDRA_TRANSID_MASK;
}