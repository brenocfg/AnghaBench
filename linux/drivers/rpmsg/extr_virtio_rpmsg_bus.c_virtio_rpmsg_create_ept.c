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
struct virtio_rpmsg_channel {int /*<<< orphan*/  vrp; } ;
struct rpmsg_endpoint {int dummy; } ;
struct rpmsg_device {int dummy; } ;
struct rpmsg_channel_info {int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  rpmsg_rx_cb_t ;

/* Variables and functions */
 struct rpmsg_endpoint* __rpmsg_create_ept (int /*<<< orphan*/ ,struct rpmsg_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct virtio_rpmsg_channel* to_virtio_rpmsg_channel (struct rpmsg_device*) ; 

__attribute__((used)) static struct rpmsg_endpoint *virtio_rpmsg_create_ept(struct rpmsg_device *rpdev,
						      rpmsg_rx_cb_t cb,
						      void *priv,
						      struct rpmsg_channel_info chinfo)
{
	struct virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(rpdev);

	return __rpmsg_create_ept(vch->vrp, rpdev, cb, priv, chinfo.src);
}