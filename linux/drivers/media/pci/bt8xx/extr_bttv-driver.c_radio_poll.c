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
struct saa6588_command {int poll_mask; int /*<<< orphan*/ * event_list; struct file* instance; } ;
struct file {struct bttv_fh* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;
struct bttv_fh {TYPE_1__ fh; struct bttv* btv; } ;
struct bttv {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLPRI ; 
 int /*<<< orphan*/  SAA6588_CMD_POLL ; 
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct saa6588_command*) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  ioctl ; 
 int poll_requested_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radio_enable (struct bttv*) ; 
 scalar_t__ v4l2_event_pending (TYPE_1__*) ; 

__attribute__((used)) static __poll_t radio_poll(struct file *file, poll_table *wait)
{
	struct bttv_fh *fh = file->private_data;
	struct bttv *btv = fh->btv;
	__poll_t req_events = poll_requested_events(wait);
	struct saa6588_command cmd;
	__poll_t res = 0;

	if (v4l2_event_pending(&fh->fh))
		res = EPOLLPRI;
	else if (req_events & EPOLLPRI)
		poll_wait(file, &fh->fh.wait, wait);
	radio_enable(btv);
	cmd.instance = file;
	cmd.event_list = wait;
	cmd.poll_mask = res;
	bttv_call_all(btv, core, ioctl, SAA6588_CMD_POLL, &cmd);

	return cmd.poll_mask;
}