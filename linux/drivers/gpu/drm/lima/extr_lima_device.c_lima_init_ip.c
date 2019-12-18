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
struct lima_ip_desc {int* offset; int* must_have; int (* init ) (struct lima_ip*) ;scalar_t__ irq_name; } ;
struct lima_ip {int id; int irq; int present; scalar_t__ iomem; struct lima_device* dev; } ;
struct lima_device {size_t id; int /*<<< orphan*/  pdev; scalar_t__ iomem; struct lima_ip* ip; } ;

/* Variables and functions */
 struct lima_ip_desc* lima_ip_desc ; 
 int platform_get_irq_byname (int /*<<< orphan*/ ,scalar_t__) ; 
 int stub1 (struct lima_ip*) ; 

__attribute__((used)) static int lima_init_ip(struct lima_device *dev, int index)
{
	struct lima_ip_desc *desc = lima_ip_desc + index;
	struct lima_ip *ip = dev->ip + index;
	int offset = desc->offset[dev->id];
	bool must = desc->must_have[dev->id];
	int err;

	if (offset < 0)
		return 0;

	ip->dev = dev;
	ip->id = index;
	ip->iomem = dev->iomem + offset;
	if (desc->irq_name) {
		err = platform_get_irq_byname(dev->pdev, desc->irq_name);
		if (err < 0)
			goto out;
		ip->irq = err;
	}

	err = desc->init(ip);
	if (!err) {
		ip->present = true;
		return 0;
	}

out:
	return must ? err : 0;
}