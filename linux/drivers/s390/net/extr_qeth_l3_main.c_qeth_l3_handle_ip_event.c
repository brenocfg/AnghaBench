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
struct qeth_ipaddr {int dummy; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  qeth_l3_modify_ip (struct qeth_card*,struct qeth_ipaddr*,int) ; 

__attribute__((used)) static int qeth_l3_handle_ip_event(struct qeth_card *card,
				   struct qeth_ipaddr *addr,
				   unsigned long event)
{
	switch (event) {
	case NETDEV_UP:
		qeth_l3_modify_ip(card, addr, true);
		return NOTIFY_OK;
	case NETDEV_DOWN:
		qeth_l3_modify_ip(card, addr, false);
		return NOTIFY_OK;
	default:
		return NOTIFY_DONE;
	}
}