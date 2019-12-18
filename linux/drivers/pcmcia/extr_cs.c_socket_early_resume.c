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
struct pcmcia_socket {int state; int /*<<< orphan*/  ops_mutex; int /*<<< orphan*/  resume_status; int /*<<< orphan*/  socket; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_socket ) (struct pcmcia_socket*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* init ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 int SOCKET_IN_RESUME ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resume_delay ; 
 int /*<<< orphan*/  socket_setup (struct pcmcia_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int socket_early_resume(struct pcmcia_socket *skt)
{
	mutex_lock(&skt->ops_mutex);
	skt->socket = dead_socket;
	skt->ops->init(skt);
	skt->ops->set_socket(skt, &skt->socket);
	if (skt->state & SOCKET_PRESENT)
		skt->resume_status = socket_setup(skt, resume_delay);
	skt->state |= SOCKET_IN_RESUME;
	mutex_unlock(&skt->ops_mutex);
	return 0;
}