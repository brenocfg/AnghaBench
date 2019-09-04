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
struct io_thread_req {scalar_t__ op; int error; int length; int sectorsize; char* buffer; int /*<<< orphan*/ * fds; scalar_t__* offsets; scalar_t__ offset; int /*<<< orphan*/  sector_mask; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 scalar_t__ UBD_FLUSH ; 
 scalar_t__ UBD_READ ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int os_pread_file (int /*<<< orphan*/ ,char*,unsigned long,scalar_t__) ; 
 int os_pwrite_file (int /*<<< orphan*/ ,char*,unsigned long,scalar_t__) ; 
 int os_sync_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 
 int ubd_test_bit (int,unsigned char*) ; 
 int update_bitmap (struct io_thread_req*) ; 

__attribute__((used)) static void do_io(struct io_thread_req *req)
{
	char *buf;
	unsigned long len;
	int n, nsectors, start, end, bit;
	__u64 off;

	if (req->op == UBD_FLUSH) {
		/* fds[0] is always either the rw image or our cow file */
		n = os_sync_file(req->fds[0]);
		if (n != 0) {
			printk("do_io - sync failed err = %d "
			       "fd = %d\n", -n, req->fds[0]);
			req->error = 1;
		}
		return;
	}

	nsectors = req->length / req->sectorsize;
	start = 0;
	do {
		bit = ubd_test_bit(start, (unsigned char *) &req->sector_mask);
		end = start;
		while((end < nsectors) &&
		      (ubd_test_bit(end, (unsigned char *)
				    &req->sector_mask) == bit))
			end++;

		off = req->offset + req->offsets[bit] +
			start * req->sectorsize;
		len = (end - start) * req->sectorsize;
		buf = &req->buffer[start * req->sectorsize];

		if(req->op == UBD_READ){
			n = 0;
			do {
				buf = &buf[n];
				len -= n;
				n = os_pread_file(req->fds[bit], buf, len, off);
				if (n < 0) {
					printk("do_io - read failed, err = %d "
					       "fd = %d\n", -n, req->fds[bit]);
					req->error = 1;
					return;
				}
			} while((n < len) && (n != 0));
			if (n < len) memset(&buf[n], 0, len - n);
		} else {
			n = os_pwrite_file(req->fds[bit], buf, len, off);
			if(n != len){
				printk("do_io - write failed err = %d "
				       "fd = %d\n", -n, req->fds[bit]);
				req->error = 1;
				return;
			}
		}

		start = end;
	} while(start < nsectors);

	req->error = update_bitmap(req);
}