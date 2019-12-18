#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ngene_channel {int /*<<< orphan*/ * fe; int /*<<< orphan*/  i2c_adapter; TYPE_2__* dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pci_dev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  aver_m780 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  lgdt330x_attach ; 
 int /*<<< orphan*/  m780_tunerconfig ; 
 int /*<<< orphan*/  mt2131_attach ; 

__attribute__((used)) static int demod_attach_lg330x(struct ngene_channel *chan)
{
	struct device *pdev = &chan->dev->pci_dev->dev;

	chan->fe = dvb_attach(lgdt330x_attach, &aver_m780,
			      0xb2 >> 1, &chan->i2c_adapter);
	if (chan->fe == NULL) {
		dev_err(pdev, "No LGDT330x found!\n");
		return -ENODEV;
	}

	dvb_attach(mt2131_attach, chan->fe, &chan->i2c_adapter,
		   &m780_tunerconfig, 0);

	return (chan->fe) ? 0 : -ENODEV;
}