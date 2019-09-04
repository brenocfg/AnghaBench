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
struct TYPE_2__ {int /*<<< orphan*/  bitmap_len; int /*<<< orphan*/  bitmap_offset; int /*<<< orphan*/  bitmap; int /*<<< orphan*/ * file; int /*<<< orphan*/  data_offset; int /*<<< orphan*/  fd; } ;
struct ubd {TYPE_1__ cow; int /*<<< orphan*/  fd; } ;
struct request {struct gendisk* rq_disk; } ;
struct page {int dummy; } ;
struct io_thread_req {int cow_offset; unsigned long long offset; int length; int sectorsize; scalar_t__ buffer; int /*<<< orphan*/ * offsets; int /*<<< orphan*/  op; scalar_t__ sector_mask; scalar_t__ error; int /*<<< orphan*/ * fds; struct request* req; } ;
struct gendisk {struct ubd* private_data; } ;

/* Variables and functions */
 scalar_t__ READ ; 
 int /*<<< orphan*/  UBD_READ ; 
 int /*<<< orphan*/  UBD_WRITE ; 
 int /*<<< orphan*/  cowify_req (struct io_thread_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static void prepare_request(struct request *req, struct io_thread_req *io_req,
			    unsigned long long offset, int page_offset,
			    int len, struct page *page)
{
	struct gendisk *disk = req->rq_disk;
	struct ubd *ubd_dev = disk->private_data;

	io_req->req = req;
	io_req->fds[0] = (ubd_dev->cow.file != NULL) ? ubd_dev->cow.fd :
		ubd_dev->fd;
	io_req->fds[1] = ubd_dev->fd;
	io_req->cow_offset = -1;
	io_req->offset = offset;
	io_req->length = len;
	io_req->error = 0;
	io_req->sector_mask = 0;

	io_req->op = (rq_data_dir(req) == READ) ? UBD_READ : UBD_WRITE;
	io_req->offsets[0] = 0;
	io_req->offsets[1] = ubd_dev->cow.data_offset;
	io_req->buffer = page_address(page) + page_offset;
	io_req->sectorsize = 1 << 9;

	if(ubd_dev->cow.file != NULL)
		cowify_req(io_req, ubd_dev->cow.bitmap,
			   ubd_dev->cow.bitmap_offset, ubd_dev->cow.bitmap_len);

}