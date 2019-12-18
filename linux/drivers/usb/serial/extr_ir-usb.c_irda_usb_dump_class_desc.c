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
struct usb_serial {TYPE_1__* dev; } ;
struct usb_irda_cs_descriptor {int /*<<< orphan*/  bMaxUnicastList; int /*<<< orphan*/  bIrdaRateSniff; int /*<<< orphan*/  bmAdditionalBOFs; int /*<<< orphan*/  wBaudRate; int /*<<< orphan*/  bmMinTurnaroundTime; int /*<<< orphan*/  bmWindowSize; int /*<<< orphan*/  bmDataSize; int /*<<< orphan*/  bcdSpecRevision; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void irda_usb_dump_class_desc(struct usb_serial *serial,
					    struct usb_irda_cs_descriptor *desc)
{
	struct device *dev = &serial->dev->dev;

	dev_dbg(dev, "bLength=%x\n", desc->bLength);
	dev_dbg(dev, "bDescriptorType=%x\n", desc->bDescriptorType);
	dev_dbg(dev, "bcdSpecRevision=%x\n", __le16_to_cpu(desc->bcdSpecRevision));
	dev_dbg(dev, "bmDataSize=%x\n", desc->bmDataSize);
	dev_dbg(dev, "bmWindowSize=%x\n", desc->bmWindowSize);
	dev_dbg(dev, "bmMinTurnaroundTime=%d\n", desc->bmMinTurnaroundTime);
	dev_dbg(dev, "wBaudRate=%x\n", __le16_to_cpu(desc->wBaudRate));
	dev_dbg(dev, "bmAdditionalBOFs=%x\n", desc->bmAdditionalBOFs);
	dev_dbg(dev, "bIrdaRateSniff=%x\n", desc->bIrdaRateSniff);
	dev_dbg(dev, "bMaxUnicastList=%x\n", desc->bMaxUnicastList);
}