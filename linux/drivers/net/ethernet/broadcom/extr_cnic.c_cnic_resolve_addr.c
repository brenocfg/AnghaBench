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
struct cnic_sockaddr {int dummy; } ;
struct cnic_sock {struct cnic_dev* dev; } ;
struct cnic_local {int dummy; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_KEVENT_PATH_REQ ; 
 int cnic_send_nlmsg (struct cnic_local*,int /*<<< orphan*/ ,struct cnic_sock*) ; 

__attribute__((used)) static int cnic_resolve_addr(struct cnic_sock *csk, struct cnic_sockaddr *saddr)
{
	struct cnic_dev *dev = csk->dev;
	struct cnic_local *cp = dev->cnic_priv;

	return cnic_send_nlmsg(cp, ISCSI_KEVENT_PATH_REQ, csk);
}