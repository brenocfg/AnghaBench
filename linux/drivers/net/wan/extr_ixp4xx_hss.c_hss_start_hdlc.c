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
struct port {int /*<<< orphan*/  id; } ;
struct msg {scalar_t__ data32; int /*<<< orphan*/  hss_port; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  PKT_PIPE_FLOW_ENABLE ; 
 int /*<<< orphan*/  hss_npe_send (struct port*,struct msg*,char*) ; 
 int /*<<< orphan*/  memset (struct msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hss_start_hdlc(struct port *port)
{
	struct msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = PKT_PIPE_FLOW_ENABLE;
	msg.hss_port = port->id;
	msg.data32 = 0;
	hss_npe_send(port, &msg, "HSS_ENABLE_PKT_PIPE");
}