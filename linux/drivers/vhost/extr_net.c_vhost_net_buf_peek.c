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
struct vhost_net_buf {int dummy; } ;
struct vhost_net_virtqueue {struct vhost_net_buf rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  vhost_net_buf_get_ptr (struct vhost_net_buf*) ; 
 int /*<<< orphan*/  vhost_net_buf_is_empty (struct vhost_net_buf*) ; 
 int vhost_net_buf_peek_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_net_buf_produce (struct vhost_net_virtqueue*) ; 

__attribute__((used)) static int vhost_net_buf_peek(struct vhost_net_virtqueue *nvq)
{
	struct vhost_net_buf *rxq = &nvq->rxq;

	if (!vhost_net_buf_is_empty(rxq))
		goto out;

	if (!vhost_net_buf_produce(nvq))
		return 0;

out:
	return vhost_net_buf_peek_len(vhost_net_buf_get_ptr(rxq));
}