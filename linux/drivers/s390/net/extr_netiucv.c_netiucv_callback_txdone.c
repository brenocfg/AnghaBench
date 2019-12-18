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
struct iucv_path {struct iucv_connection* private; } ;
struct iucv_message {int dummy; } ;
struct iucv_event {struct iucv_message* data; struct iucv_connection* conn; } ;
struct iucv_connection {int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_EVENT_TXDONE ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iucv_event*) ; 

__attribute__((used)) static void netiucv_callback_txdone(struct iucv_path *path,
				    struct iucv_message *msg)
{
	struct iucv_connection *conn = path->private;
	struct iucv_event ev;

	ev.conn = conn;
	ev.data = msg;
	fsm_event(conn->fsm, CONN_EVENT_TXDONE, &ev);
}