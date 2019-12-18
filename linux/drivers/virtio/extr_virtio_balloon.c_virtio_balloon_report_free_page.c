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
struct virtio_balloon {TYPE_1__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int send_cmd_id_start (struct virtio_balloon*) ; 
 int send_cmd_id_stop (struct virtio_balloon*) ; 
 int send_free_pages (struct virtio_balloon*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void virtio_balloon_report_free_page(struct virtio_balloon *vb)
{
	int err;
	struct device *dev = &vb->vdev->dev;

	/* Start by sending the received cmd id to host with an outbuf. */
	err = send_cmd_id_start(vb);
	if (unlikely(err))
		dev_err(dev, "Failed to send a start id, err = %d\n", err);

	err = send_free_pages(vb);
	if (unlikely(err))
		dev_err(dev, "Failed to send a free page, err = %d\n", err);

	/* End by sending a stop id to host with an outbuf. */
	err = send_cmd_id_stop(vb);
	if (unlikely(err))
		dev_err(dev, "Failed to send a stop id, err = %d\n", err);
}