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
struct uwb_rceb {int dummy; } ;
struct uwb_rc_cmd_done_params {int /*<<< orphan*/  completion; int /*<<< orphan*/  reply_size; scalar_t__ reply; } ;
struct uwb_rc {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct uwb_rceb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uwb_rc_cmd_done(struct uwb_rc *rc, void *arg,
			    struct uwb_rceb *reply, ssize_t reply_size)
{
	struct uwb_rc_cmd_done_params *p = (struct uwb_rc_cmd_done_params *)arg;

	if (reply_size > 0) {
		if (p->reply)
			reply_size = min(p->reply_size, reply_size);
		else
			p->reply = kmalloc(reply_size, GFP_ATOMIC);

		if (p->reply)
			memcpy(p->reply, reply, reply_size);
		else
			reply_size = -ENOMEM;
	}
	p->reply_size = reply_size;
	complete(&p->completion);
}