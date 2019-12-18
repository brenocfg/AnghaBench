#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct sock_mapping {scalar_t__ active_socket; } ;
struct pvcalls_bedata {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLNVAL ; 
 scalar_t__ IS_ERR (struct sock_mapping*) ; 
 struct pvcalls_bedata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct sock_mapping* pvcalls_enter_sock (struct socket*) ; 
 int /*<<< orphan*/  pvcalls_exit_sock (struct socket*) ; 
 TYPE_1__* pvcalls_front_dev ; 
 int /*<<< orphan*/  pvcalls_front_poll_active (struct file*,struct pvcalls_bedata*,struct sock_mapping*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvcalls_front_poll_passive (struct file*,struct pvcalls_bedata*,struct sock_mapping*,int /*<<< orphan*/ *) ; 

__poll_t pvcalls_front_poll(struct file *file, struct socket *sock,
			       poll_table *wait)
{
	struct pvcalls_bedata *bedata;
	struct sock_mapping *map;
	__poll_t ret;

	map = pvcalls_enter_sock(sock);
	if (IS_ERR(map))
		return EPOLLNVAL;
	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);

	if (map->active_socket)
		ret = pvcalls_front_poll_active(file, bedata, map, wait);
	else
		ret = pvcalls_front_poll_passive(file, bedata, map, wait);
	pvcalls_exit_sock(sock);
	return ret;
}