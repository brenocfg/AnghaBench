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
struct lima_ip {int /*<<< orphan*/  irq; struct lima_device* dev; } ;
struct lima_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lima_ip*) ; 
 int /*<<< orphan*/  lima_ip_name (struct lima_ip*) ; 
 int /*<<< orphan*/  lima_pp_bcast_irq_handler ; 

int lima_pp_bcast_init(struct lima_ip *ip)
{
	struct lima_device *dev = ip->dev;
	int err;

	err = devm_request_irq(dev->dev, ip->irq, lima_pp_bcast_irq_handler,
			       IRQF_SHARED, lima_ip_name(ip), ip);
	if (err) {
		dev_err(dev->dev, "pp %s fail to request irq\n",
			lima_ip_name(ip));
		return err;
	}

	return 0;
}