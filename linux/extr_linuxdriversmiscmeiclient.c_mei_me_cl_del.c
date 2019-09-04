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
struct mei_me_client {int dummy; } ;
struct mei_device {int /*<<< orphan*/  me_clients_rwsem; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mei_me_cl_del (struct mei_device*,struct mei_me_client*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void mei_me_cl_del(struct mei_device *dev, struct mei_me_client *me_cl)
{
	down_write(&dev->me_clients_rwsem);
	__mei_me_cl_del(dev, me_cl);
	up_write(&dev->me_clients_rwsem);
}