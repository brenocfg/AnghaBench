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
struct tcpm_port {int /*<<< orphan*/  vdm_state_machine; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 scalar_t__ CMD_ATTENTION ; 
 scalar_t__ PD_VDO_CMD (int) ; 
 int USB_SID_PD ; 
 int VDO (int,int,int) ; 
 int VDO_MAX_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_queue_vdm (struct tcpm_port*,int,int const*,int) ; 

__attribute__((used)) static void tcpm_send_vdm(struct tcpm_port *port, u32 vid, int cmd,
			  const u32 *data, int count)
{
	u32 header;

	if (WARN_ON(count > VDO_MAX_SIZE - 1))
		count = VDO_MAX_SIZE - 1;

	/* set VDM header with VID & CMD */
	header = VDO(vid, ((vid & USB_SID_PD) == USB_SID_PD) ?
			1 : (PD_VDO_CMD(cmd) <= CMD_ATTENTION), cmd);
	tcpm_queue_vdm(port, header, data, count);

	mod_delayed_work(port->wq, &port->vdm_state_machine, 0);
}