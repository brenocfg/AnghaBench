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
typedef  int /*<<< orphan*/  u32 ;
struct tmComResInterfaceDescr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  BARLocation; int /*<<< orphan*/  bDebugInterruptId; int /*<<< orphan*/  bInterruptId; int /*<<< orphan*/  bBaseInterface; int /*<<< orphan*/  bInterfaceId; int /*<<< orphan*/  bInterfaceType; int /*<<< orphan*/  bFlags; int /*<<< orphan*/  bDescriptorSubtype; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct saa7164_dev {TYPE_1__ intfdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,TYPE_1__*,...) ; 

__attribute__((used)) static void saa7164_dump_intfdesc(struct saa7164_dev *dev)
{
	dprintk(1, "@0x%p intfdesc sizeof(struct tmComResInterfaceDescr) = %d bytes\n",
		&dev->intfdesc, (u32)sizeof(struct tmComResInterfaceDescr));

	dprintk(1, " .bLength = 0x%x\n", dev->intfdesc.bLength);
	dprintk(1, " .bDescriptorType = 0x%x\n", dev->intfdesc.bDescriptorType);
	dprintk(1, " .bDescriptorSubtype = 0x%x\n",
		dev->intfdesc.bDescriptorSubtype);

	dprintk(1, " .bFlags = 0x%x\n", dev->intfdesc.bFlags);
	dprintk(1, " .bInterfaceType = 0x%x\n", dev->intfdesc.bInterfaceType);
	dprintk(1, " .bInterfaceId = 0x%x\n", dev->intfdesc.bInterfaceId);
	dprintk(1, " .bBaseInterface = 0x%x\n", dev->intfdesc.bBaseInterface);
	dprintk(1, " .bInterruptId = 0x%x\n", dev->intfdesc.bInterruptId);
	dprintk(1, " .bDebugInterruptId = 0x%x\n",
		dev->intfdesc.bDebugInterruptId);

	dprintk(1, " .BARLocation = 0x%x\n", dev->intfdesc.BARLocation);
}