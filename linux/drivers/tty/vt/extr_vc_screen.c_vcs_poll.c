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
struct vcs_poll_data {int event; int /*<<< orphan*/  waitq; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int DEFAULT_POLLMASK ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLPRI ; 
#define  VT_DEALLOCATE 129 
#define  VT_UPDATE 128 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vcs_poll_data* vcs_poll_data_get (struct file*) ; 

__attribute__((used)) static __poll_t
vcs_poll(struct file *file, poll_table *wait)
{
	struct vcs_poll_data *poll = vcs_poll_data_get(file);
	__poll_t ret = DEFAULT_POLLMASK|EPOLLERR;

	if (poll) {
		poll_wait(file, &poll->waitq, wait);
		switch (poll->event) {
		case VT_UPDATE:
			ret = DEFAULT_POLLMASK|EPOLLPRI;
			break;
		case VT_DEALLOCATE:
			ret = DEFAULT_POLLMASK|EPOLLHUP|EPOLLERR;
			break;
		case 0:
			ret = DEFAULT_POLLMASK;
			break;
		}
	}
	return ret;
}