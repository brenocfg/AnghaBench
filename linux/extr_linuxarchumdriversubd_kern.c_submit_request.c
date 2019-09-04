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
struct ubd {int /*<<< orphan*/  restart; } ;
struct io_thread_req {int dummy; } ;
typedef  int /*<<< orphan*/  io_req ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  kfree (struct io_thread_req*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int os_write_file (int /*<<< orphan*/ ,struct io_thread_req**,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  restart ; 
 int /*<<< orphan*/  thread_fd ; 

__attribute__((used)) static bool submit_request(struct io_thread_req *io_req, struct ubd *dev)
{
	int n = os_write_file(thread_fd, &io_req,
			     sizeof(io_req));
	if (n != sizeof(io_req)) {
		if (n != -EAGAIN)
			printk("write to io thread failed, "
			       "errno = %d\n", -n);
		else if (list_empty(&dev->restart))
			list_add(&dev->restart, &restart);

		kfree(io_req);
		return false;
	}
	return true;
}