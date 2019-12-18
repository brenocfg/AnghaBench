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
struct port {int hdlc_cfg; int /*<<< orphan*/  id; } ;
struct msg {int data8a; int data8b; int /*<<< orphan*/  hss_port; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int PKT_EXTRA_FLAGS ; 
 int /*<<< orphan*/  PKT_PIPE_HDLC_CFG_WRITE ; 
 int /*<<< orphan*/  hss_npe_send (struct port*,struct msg*,char*) ; 
 int /*<<< orphan*/  memset (struct msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hss_set_hdlc_cfg(struct port *port)
{
	struct msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = PKT_PIPE_HDLC_CFG_WRITE;
	msg.hss_port = port->id;
	msg.data8a = port->hdlc_cfg; /* rx_cfg */
	msg.data8b = port->hdlc_cfg | (PKT_EXTRA_FLAGS << 3); /* tx_cfg */
	hss_npe_send(port, &msg, "HSS_SET_HDLC_CFG");
}