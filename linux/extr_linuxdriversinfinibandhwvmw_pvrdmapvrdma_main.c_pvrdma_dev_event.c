#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pvrdma_dev {TYPE_3__* pdev; TYPE_2__* dsr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int phys_port_cnt; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pvrdma_dispatch_event (struct pvrdma_dev*,int,int) ; 

__attribute__((used)) static void pvrdma_dev_event(struct pvrdma_dev *dev, u8 port, int type)
{
	if (port < 1 || port > dev->dsr->caps.phys_port_cnt) {
		dev_warn(&dev->pdev->dev, "event on port %d\n", port);
		return;
	}

	pvrdma_dispatch_event(dev, port, type);
}