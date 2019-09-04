#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long timeout; } ;
struct nbd_device {TYPE_2__* disk; TYPE_1__ tag_set; struct nbd_config* config; } ;
struct nbd_config {unsigned long bytesize; unsigned long blksize; unsigned long flags; } ;
struct block_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 unsigned long HZ ; 
#define  NBD_CLEAR_QUE 138 
#define  NBD_CLEAR_SOCK 137 
#define  NBD_DISCONNECT 136 
#define  NBD_DO_IT 135 
#define  NBD_PRINT_DEBUG 134 
#define  NBD_SET_BLKSIZE 133 
#define  NBD_SET_FLAGS 132 
#define  NBD_SET_SIZE 131 
#define  NBD_SET_SIZE_BLOCKS 130 
#define  NBD_SET_SOCK 129 
#define  NBD_SET_TIMEOUT 128 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long div_s64 (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 int nbd_add_socket (struct nbd_device*,unsigned long,int) ; 
 int /*<<< orphan*/  nbd_clear_sock_ioctl (struct nbd_device*,struct block_device*) ; 
 int nbd_disconnect (struct nbd_device*) ; 
 int /*<<< orphan*/  nbd_size_set (struct nbd_device*,unsigned long,unsigned long) ; 
 int nbd_start_device_ioctl (struct nbd_device*,struct block_device*) ; 

__attribute__((used)) static int __nbd_ioctl(struct block_device *bdev, struct nbd_device *nbd,
		       unsigned int cmd, unsigned long arg)
{
	struct nbd_config *config = nbd->config;

	switch (cmd) {
	case NBD_DISCONNECT:
		return nbd_disconnect(nbd);
	case NBD_CLEAR_SOCK:
		nbd_clear_sock_ioctl(nbd, bdev);
		return 0;
	case NBD_SET_SOCK:
		return nbd_add_socket(nbd, arg, false);
	case NBD_SET_BLKSIZE:
		if (!arg || !is_power_of_2(arg) || arg < 512 ||
		    arg > PAGE_SIZE)
			return -EINVAL;
		nbd_size_set(nbd, arg,
			     div_s64(config->bytesize, arg));
		return 0;
	case NBD_SET_SIZE:
		nbd_size_set(nbd, config->blksize,
			     div_s64(arg, config->blksize));
		return 0;
	case NBD_SET_SIZE_BLOCKS:
		nbd_size_set(nbd, config->blksize, arg);
		return 0;
	case NBD_SET_TIMEOUT:
		if (arg) {
			nbd->tag_set.timeout = arg * HZ;
			blk_queue_rq_timeout(nbd->disk->queue, arg * HZ);
		}
		return 0;

	case NBD_SET_FLAGS:
		config->flags = arg;
		return 0;
	case NBD_DO_IT:
		return nbd_start_device_ioctl(nbd, bdev);
	case NBD_CLEAR_QUE:
		/*
		 * This is for compatibility only.  The queue is always cleared
		 * by NBD_DO_IT or NBD_CLEAR_SOCK.
		 */
		return 0;
	case NBD_PRINT_DEBUG:
		/*
		 * For compatibility only, we no longer keep a list of
		 * outstanding requests.
		 */
		return 0;
	}
	return -ENOTTY;
}