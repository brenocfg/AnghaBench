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
struct socket {int /*<<< orphan*/  state; } ;
struct atm_vcc {int dummy; } ;

/* Variables and functions */
#define  ATMTCP_CREATE 130 
#define  ATMTCP_REMOVE 129 
 struct atm_vcc* ATM_SD (struct socket*) ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int ENOIOCTLCMD ; 
 int EPERM ; 
#define  SIOCSIFATMTCP 128 
 int /*<<< orphan*/  SS_CONNECTED ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int atmtcp_attach (struct atm_vcc*,int) ; 
 int atmtcp_create_persistent (int) ; 
 int atmtcp_remove_persistent (int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmtcp_ioctl(struct socket *sock, unsigned int cmd, unsigned long arg)
{
	int err = 0;
	struct atm_vcc *vcc = ATM_SD(sock);

	if (cmd != SIOCSIFATMTCP && cmd != ATMTCP_CREATE && cmd != ATMTCP_REMOVE)
		return -ENOIOCTLCMD;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	switch (cmd) {
		case SIOCSIFATMTCP:
			err = atmtcp_attach(vcc, (int) arg);
			if (err >= 0) {
				sock->state = SS_CONNECTED;
				__module_get(THIS_MODULE);
			}
			break;
		case ATMTCP_CREATE:
			err = atmtcp_create_persistent((int) arg);
			break;
		case ATMTCP_REMOVE:
			err = atmtcp_remove_persistent((int) arg);
			break;
	}
	return err;
}