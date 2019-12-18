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
struct scifmsg {int /*<<< orphan*/  uop; } ;
struct scif_dev {int /*<<< orphan*/  node; TYPE_1__* sdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scif_msg_unknown(struct scif_dev *scifdev, struct scifmsg *msg)
{
	/* Bogus Node Qp Message? */
	dev_err(&scifdev->sdev->dev,
		"Unknown message 0x%xn scifdev->node 0x%x\n",
		msg->uop, scifdev->node);
}