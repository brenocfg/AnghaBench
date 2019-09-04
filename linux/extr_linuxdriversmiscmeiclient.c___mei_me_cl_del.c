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
struct mei_me_client {int /*<<< orphan*/  list; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mei_me_cl_put (struct mei_me_client*) ; 

__attribute__((used)) static void __mei_me_cl_del(struct mei_device *dev, struct mei_me_client *me_cl)
{
	if (!me_cl)
		return;

	list_del_init(&me_cl->list);
	mei_me_cl_put(me_cl);
}