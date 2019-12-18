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
struct port {int /*<<< orphan*/  npe; int /*<<< orphan*/  id; } ;
struct msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  npe_name (int /*<<< orphan*/ ) ; 
 scalar_t__ npe_send_message (int /*<<< orphan*/ ,struct msg*,char const*) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hss_npe_send(struct port *port, struct msg *msg, const char* what)
{
	u32 *val = (u32*)msg;
	if (npe_send_message(port->npe, msg, what)) {
		pr_crit("HSS-%i: unable to send command [%08X:%08X] to %s\n",
			port->id, val[0], val[1], npe_name(port->npe));
		BUG();
	}
}