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
struct tmComResHWDescr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dwHostHibernatMemRegionSize; int /*<<< orphan*/  dwHostHibernatMemRegion; int /*<<< orphan*/  dwHostMemoryRegionSize; int /*<<< orphan*/  dwHostMemoryRegion; int /*<<< orphan*/  dwDeviceRegistersLocation; int /*<<< orphan*/  bCapabilities; int /*<<< orphan*/  dwClockUpdateRes; int /*<<< orphan*/  dwClockFrequency; int /*<<< orphan*/  bcdSpecVersion; int /*<<< orphan*/  bDescriptorSubtype; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct saa7164_dev {TYPE_1__ hwdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,TYPE_1__*,...) ; 

__attribute__((used)) static void saa7164_dump_hwdesc(struct saa7164_dev *dev)
{
	dprintk(1, "@0x%p hwdesc sizeof(struct tmComResHWDescr) = %d bytes\n",
		&dev->hwdesc, (u32)sizeof(struct tmComResHWDescr));

	dprintk(1, " .bLength = 0x%x\n", dev->hwdesc.bLength);
	dprintk(1, " .bDescriptorType = 0x%x\n", dev->hwdesc.bDescriptorType);
	dprintk(1, " .bDescriptorSubtype = 0x%x\n",
		dev->hwdesc.bDescriptorSubtype);

	dprintk(1, " .bcdSpecVersion = 0x%x\n", dev->hwdesc.bcdSpecVersion);
	dprintk(1, " .dwClockFrequency = 0x%x\n", dev->hwdesc.dwClockFrequency);
	dprintk(1, " .dwClockUpdateRes = 0x%x\n", dev->hwdesc.dwClockUpdateRes);
	dprintk(1, " .bCapabilities = 0x%x\n", dev->hwdesc.bCapabilities);
	dprintk(1, " .dwDeviceRegistersLocation = 0x%x\n",
		dev->hwdesc.dwDeviceRegistersLocation);

	dprintk(1, " .dwHostMemoryRegion = 0x%x\n",
		dev->hwdesc.dwHostMemoryRegion);

	dprintk(1, " .dwHostMemoryRegionSize = 0x%x\n",
		dev->hwdesc.dwHostMemoryRegionSize);

	dprintk(1, " .dwHostHibernatMemRegion = 0x%x\n",
		dev->hwdesc.dwHostHibernatMemRegion);

	dprintk(1, " .dwHostHibernatMemRegionSize = 0x%x\n",
		dev->hwdesc.dwHostHibernatMemRegionSize);
}