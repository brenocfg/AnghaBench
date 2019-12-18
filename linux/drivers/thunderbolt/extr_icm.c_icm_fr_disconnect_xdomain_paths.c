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
typedef  scalar_t__ u8 ;
struct tb_xdomain {int /*<<< orphan*/  link; } ;
struct tb {int /*<<< orphan*/  nhi; } ;

/* Variables and functions */
 scalar_t__ NHI_MAILBOX_DISCONNECT_PA ; 
 scalar_t__ NHI_MAILBOX_DISCONNECT_PB ; 
 int /*<<< orphan*/  nhi_mailbox_cmd (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ tb_phy_port_from_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int icm_fr_disconnect_xdomain_paths(struct tb *tb, struct tb_xdomain *xd)
{
	u8 phy_port;
	u8 cmd;

	phy_port = tb_phy_port_from_link(xd->link);
	if (phy_port == 0)
		cmd = NHI_MAILBOX_DISCONNECT_PA;
	else
		cmd = NHI_MAILBOX_DISCONNECT_PB;

	nhi_mailbox_cmd(tb->nhi, cmd, 1);
	usleep_range(10, 50);
	nhi_mailbox_cmd(tb->nhi, cmd, 2);
	return 0;
}