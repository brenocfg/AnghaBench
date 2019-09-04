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
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/ * file; } ;
struct ubd {int /*<<< orphan*/  fd; TYPE_1__ cow; } ;
struct request {struct gendisk* rq_disk; } ;
struct io_thread_req {int /*<<< orphan*/  op; int /*<<< orphan*/ * fds; struct request* req; } ;
struct gendisk {struct ubd* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBD_FLUSH ; 

__attribute__((used)) static void prepare_flush_request(struct request *req,
				  struct io_thread_req *io_req)
{
	struct gendisk *disk = req->rq_disk;
	struct ubd *ubd_dev = disk->private_data;

	io_req->req = req;
	io_req->fds[0] = (ubd_dev->cow.file != NULL) ? ubd_dev->cow.fd :
		ubd_dev->fd;
	io_req->op = UBD_FLUSH;
}