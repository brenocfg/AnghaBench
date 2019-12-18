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
struct vhost_virtqueue {int /*<<< orphan*/  iov; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,size_t) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_init (struct iov_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 
 size_t iov_length (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t init_iov_iter(struct vhost_virtqueue *vq, struct iov_iter *iter,
			    size_t hdr_size, int out)
{
	/* Skip header. TODO: support TSO. */
	size_t len = iov_length(vq->iov, out);

	iov_iter_init(iter, WRITE, vq->iov, out, len);
	iov_iter_advance(iter, hdr_size);

	return iov_iter_count(iter);
}