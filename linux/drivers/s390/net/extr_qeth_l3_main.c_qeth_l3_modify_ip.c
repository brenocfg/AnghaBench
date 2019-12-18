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
struct qeth_card {int /*<<< orphan*/  ip_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qeth_l3_add_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 int qeth_l3_delete_ip (struct qeth_card*,struct qeth_ipaddr*) ; 

__attribute__((used)) static int qeth_l3_modify_ip(struct qeth_card *card, struct qeth_ipaddr *addr,
			     bool add)
{
	int rc;

	mutex_lock(&card->ip_lock);
	rc = add ? qeth_l3_add_ip(card, addr) : qeth_l3_delete_ip(card, addr);
	mutex_unlock(&card->ip_lock);

	return rc;
}