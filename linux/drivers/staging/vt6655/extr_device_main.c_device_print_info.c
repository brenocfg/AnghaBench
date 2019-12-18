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
struct vnt_private {TYPE_1__* pcid; scalar_t__ PortOffset; scalar_t__ ioaddr; int /*<<< orphan*/  abyCurrentNetAddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_print_info(struct vnt_private *priv)
{
	dev_info(&priv->pcid->dev, "MAC=%pM IO=0x%lx Mem=0x%lx IRQ=%d\n",
		 priv->abyCurrentNetAddr, (unsigned long)priv->ioaddr,
		 (unsigned long)priv->PortOffset, priv->pcid->irq);
}