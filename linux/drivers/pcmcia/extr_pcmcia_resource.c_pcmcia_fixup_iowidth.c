#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_socket {int state; int /*<<< orphan*/  ops_mutex; TYPE_4__* ops; TYPE_3__* io; } ;
struct pcmcia_device {int /*<<< orphan*/  dev; TYPE_1__* function_config; struct pcmcia_socket* socket; } ;
struct TYPE_12__ {int member_4; int map; int flags; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  speed; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ pccard_io_map ;
struct TYPE_11__ {int /*<<< orphan*/  (* set_io_map ) (struct pcmcia_socket*,TYPE_5__*) ;} ;
struct TYPE_10__ {TYPE_2__* res; } ;
struct TYPE_9__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_8__ {int state; } ;

/* Variables and functions */
 int CONFIG_LOCKED ; 
 int EACCES ; 
 int IO_DATA_PATH_WIDTH_8 ; 
 int MAP_ACTIVE ; 
 int MAX_IO_WIN ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  io_speed ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*,TYPE_5__*) ; 

int pcmcia_fixup_iowidth(struct pcmcia_device *p_dev)
{
	struct pcmcia_socket *s = p_dev->socket;
	pccard_io_map io_off = { 0, 0, 0, 0, 1 };
	pccard_io_map io_on;
	int i, ret = 0;

	mutex_lock(&s->ops_mutex);

	dev_dbg(&p_dev->dev, "fixup iowidth to 8bit\n");

	if (!(s->state & SOCKET_PRESENT) ||
		!(p_dev->function_config->state & CONFIG_LOCKED)) {
		dev_dbg(&p_dev->dev, "No card? Config not locked?\n");
		ret = -EACCES;
		goto unlock;
	}

	io_on.speed = io_speed;
	for (i = 0; i < MAX_IO_WIN; i++) {
		if (!s->io[i].res)
			continue;
		io_off.map = i;
		io_on.map = i;

		io_on.flags = MAP_ACTIVE | IO_DATA_PATH_WIDTH_8;
		io_on.start = s->io[i].res->start;
		io_on.stop = s->io[i].res->end;

		s->ops->set_io_map(s, &io_off);
		msleep(40);
		s->ops->set_io_map(s, &io_on);
	}
unlock:
	mutex_unlock(&s->ops_mutex);

	return ret;
}