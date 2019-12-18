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
typedef  int /*<<< orphan*/  u32 ;
struct port {int /*<<< orphan*/  id; int /*<<< orphan*/  npe; } ;
struct msg {int /*<<< orphan*/  data32; int /*<<< orphan*/  hss_port; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  PORT_ERROR_READ ; 
 int /*<<< orphan*/  hss_npe_send (struct port*,struct msg*,char*) ; 
 int /*<<< orphan*/  memset (struct msg*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ npe_recv_message (int /*<<< orphan*/ ,struct msg*,char*) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 hss_get_status(struct port *port)
{
	struct msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = PORT_ERROR_READ;
	msg.hss_port = port->id;
	hss_npe_send(port, &msg, "PORT_ERROR_READ");
	if (npe_recv_message(port->npe, &msg, "PORT_ERROR_READ")) {
		pr_crit("HSS-%i: unable to read HSS status\n", port->id);
		BUG();
	}

	return msg.data32;
}