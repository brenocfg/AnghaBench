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
struct TYPE_2__ {int async_reset; } ;
struct lima_ip {int /*<<< orphan*/  irq; TYPE_1__ data; struct lima_device* dev; } ;
struct lima_device {int /*<<< orphan*/  gp_version; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  LIMA_GP_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lima_ip*) ; 
 int /*<<< orphan*/  gp_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_gp_irq_handler ; 
 int /*<<< orphan*/  lima_gp_print_version (struct lima_ip*) ; 
 int /*<<< orphan*/  lima_gp_soft_reset_async (struct lima_ip*) ; 
 int lima_gp_soft_reset_async_wait (struct lima_ip*) ; 
 int /*<<< orphan*/  lima_ip_name (struct lima_ip*) ; 

int lima_gp_init(struct lima_ip *ip)
{
	struct lima_device *dev = ip->dev;
	int err;

	lima_gp_print_version(ip);

	ip->data.async_reset = false;
	lima_gp_soft_reset_async(ip);
	err = lima_gp_soft_reset_async_wait(ip);
	if (err)
		return err;

	err = devm_request_irq(dev->dev, ip->irq, lima_gp_irq_handler,
			       IRQF_SHARED, lima_ip_name(ip), ip);
	if (err) {
		dev_err(dev->dev, "gp %s fail to request irq\n",
			lima_ip_name(ip));
		return err;
	}

	dev->gp_version = gp_read(LIMA_GP_VERSION);

	return 0;
}