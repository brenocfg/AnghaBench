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
struct TYPE_2__ {int msg_iovlen; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; int /*<<< orphan*/  msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; } ;
struct vector_queue {int max_depth; int max_iov_frags; struct vector_queue* mmsg_vector; scalar_t__ tail; scalar_t__ head; scalar_t__ queue_depth; int /*<<< orphan*/  tail_lock; int /*<<< orphan*/  head_lock; TYPE_1__ msg_hdr; int /*<<< orphan*/ ** skbuff_vector; int /*<<< orphan*/  dev; } ;
struct vector_private {scalar_t__ header_size; int /*<<< orphan*/  dev; } ;
struct mmsghdr {int max_depth; int max_iov_frags; struct mmsghdr* mmsg_vector; scalar_t__ tail; scalar_t__ head; scalar_t__ queue_depth; int /*<<< orphan*/  tail_lock; int /*<<< orphan*/  head_lock; TYPE_1__ msg_hdr; int /*<<< orphan*/ ** skbuff_vector; int /*<<< orphan*/  dev; } ;
struct iovec {int iov_len; int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  destroy_queue (struct vector_queue*) ; 
 int /*<<< orphan*/  kfree (struct vector_queue*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct iovec* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vector_queue *create_queue(
	struct vector_private *vp,
	int max_size,
	int header_size,
	int num_extra_frags)
{
	struct vector_queue *result;
	int i;
	struct iovec *iov;
	struct mmsghdr *mmsg_vector;

	result = kmalloc(sizeof(struct vector_queue), GFP_KERNEL);
	if (result == NULL)
		return NULL;
	result->max_depth = max_size;
	result->dev = vp->dev;
	result->mmsg_vector = kmalloc(
		(sizeof(struct mmsghdr) * max_size), GFP_KERNEL);
	if (result->mmsg_vector == NULL)
		goto out_mmsg_fail;
	result->skbuff_vector = kmalloc(
		(sizeof(void *) * max_size), GFP_KERNEL);
	if (result->skbuff_vector == NULL)
		goto out_skb_fail;

	/* further failures can be handled safely by destroy_queue*/

	mmsg_vector = result->mmsg_vector;
	for (i = 0; i < max_size; i++) {
		/* Clear all pointers - we use non-NULL as marking on
		 * what to free on destruction
		 */
		*(result->skbuff_vector + i) = NULL;
		mmsg_vector->msg_hdr.msg_iov = NULL;
		mmsg_vector++;
	}
	mmsg_vector = result->mmsg_vector;
	result->max_iov_frags = num_extra_frags;
	for (i = 0; i < max_size; i++) {
		if (vp->header_size > 0)
			iov = kmalloc_array(3 + num_extra_frags,
					    sizeof(struct iovec),
					    GFP_KERNEL
			);
		else
			iov = kmalloc_array(2 + num_extra_frags,
					    sizeof(struct iovec),
					    GFP_KERNEL
			);
		if (iov == NULL)
			goto out_fail;
		mmsg_vector->msg_hdr.msg_iov = iov;
		mmsg_vector->msg_hdr.msg_iovlen = 1;
		mmsg_vector->msg_hdr.msg_control = NULL;
		mmsg_vector->msg_hdr.msg_controllen = 0;
		mmsg_vector->msg_hdr.msg_flags = MSG_DONTWAIT;
		mmsg_vector->msg_hdr.msg_name = NULL;
		mmsg_vector->msg_hdr.msg_namelen = 0;
		if (vp->header_size > 0) {
			iov->iov_base = kmalloc(header_size, GFP_KERNEL);
			if (iov->iov_base == NULL)
				goto out_fail;
			iov->iov_len = header_size;
			mmsg_vector->msg_hdr.msg_iovlen = 2;
			iov++;
		}
		iov->iov_base = NULL;
		iov->iov_len = 0;
		mmsg_vector++;
	}
	spin_lock_init(&result->head_lock);
	spin_lock_init(&result->tail_lock);
	result->queue_depth = 0;
	result->head = 0;
	result->tail = 0;
	return result;
out_skb_fail:
	kfree(result->mmsg_vector);
out_mmsg_fail:
	kfree(result);
	return NULL;
out_fail:
	destroy_queue(result);
	return NULL;
}