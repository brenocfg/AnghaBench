#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_2__* rx; } ;
struct aac_dev {TYPE_1__ regs; int /*<<< orphan*/ * IndexRegs; TYPE_2__* base; int /*<<< orphan*/  base_start; } ;
struct TYPE_5__ {int /*<<< orphan*/  IndexRegs; } ;

/* Variables and functions */
 TYPE_2__* ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (TYPE_2__*) ; 

__attribute__((used)) static int aac_rx_ioremap(struct aac_dev * dev, u32 size)
{
	if (!size) {
		iounmap(dev->regs.rx);
		return 0;
	}
	dev->base = dev->regs.rx = ioremap(dev->base_start, size);
	if (dev->base == NULL)
		return -1;
	dev->IndexRegs = &dev->regs.rx->IndexRegs;
	return 0;
}