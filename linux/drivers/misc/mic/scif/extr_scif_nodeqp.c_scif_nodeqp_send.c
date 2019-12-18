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
struct scifmsg {scalar_t__ uop; } ;
struct scif_dev {scalar_t__ exit; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct device*) ; 
 scalar_t__ OP_IDLE ; 
 int PTR_ERR (struct device*) ; 
 scalar_t__ SCIF_EXIT_ACK ; 
 int _scif_nodeqp_send (struct scif_dev*,struct scifmsg*) ; 
 struct device* scif_get_peer_dev (struct scif_dev*) ; 
 int /*<<< orphan*/  scif_put_peer_dev (struct device*) ; 

int scif_nodeqp_send(struct scif_dev *scifdev, struct scifmsg *msg)
{
	int err;
	struct device *spdev = NULL;

	if (msg->uop > SCIF_EXIT_ACK) {
		/* Dont send messages once the exit flow has begun */
		if (OP_IDLE != scifdev->exit)
			return -ENODEV;
		spdev = scif_get_peer_dev(scifdev);
		if (IS_ERR(spdev)) {
			err = PTR_ERR(spdev);
			return err;
		}
	}
	err = _scif_nodeqp_send(scifdev, msg);
	if (msg->uop > SCIF_EXIT_ACK)
		scif_put_peer_dev(spdev);
	return err;
}