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
struct TYPE_2__ {scalar_t__ fixed_address; } ;
struct mei_me_client {scalar_t__ connect_count; TYPE_1__ props; } ;
struct mei_cl {struct mei_me_client* me_cl; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  MEI_FILE_CONNECTING ; 
 int /*<<< orphan*/  mei_me_cl_get (struct mei_me_client*) ; 
 int /*<<< orphan*/  mei_me_cl_put (struct mei_me_client*) ; 

__attribute__((used)) static int mei_cl_set_connecting(struct mei_cl *cl, struct mei_me_client *me_cl)
{
	if (!mei_me_cl_get(me_cl))
		return -ENOENT;

	/* only one connection is allowed for fixed address clients */
	if (me_cl->props.fixed_address) {
		if (me_cl->connect_count) {
			mei_me_cl_put(me_cl);
			return -EBUSY;
		}
	}

	cl->me_cl = me_cl;
	cl->state = MEI_FILE_CONNECTING;
	cl->me_cl->connect_count++;

	return 0;
}