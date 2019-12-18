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
struct ipoctal {struct ipack_device* dev; } ;
struct ipack_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  slot; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_nr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct ipoctal*) ; 
 int ipoctal_inst_slot (struct ipoctal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipoctal*) ; 
 struct ipoctal* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipoctal_probe(struct ipack_device *dev)
{
	int res;
	struct ipoctal *ipoctal;

	ipoctal = kzalloc(sizeof(struct ipoctal), GFP_KERNEL);
	if (ipoctal == NULL)
		return -ENOMEM;

	ipoctal->dev = dev;
	res = ipoctal_inst_slot(ipoctal, dev->bus->bus_nr, dev->slot);
	if (res)
		goto out_uninst;

	dev_set_drvdata(&dev->dev, ipoctal);
	return 0;

out_uninst:
	kfree(ipoctal);
	return res;
}