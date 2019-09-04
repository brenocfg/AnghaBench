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
struct grpci2_priv {unsigned int pci_conf; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  sts_cap; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LEON3_BYPASS_STORE_PA (unsigned int*,int /*<<< orphan*/ ) ; 
 int REGLOAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGSTORE (int /*<<< orphan*/ ,int) ; 
 int STS_CFGERR ; 
 int STS_CFGERRVALID ; 
 unsigned int TGT ; 
 int /*<<< orphan*/  grpci2_dev_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  swab32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int grpci2_cfg_w32(struct grpci2_priv *priv, unsigned int bus,
				unsigned int devfn, int where, u32 val)
{
	unsigned int *pci_conf;
	unsigned long flags;

	if (where & 0x3)
		return -EINVAL;

	if (bus == 0) {
		devfn += (0x8 * 6); /* start at AD16=Device0 */
	} else if (bus == TGT) {
		bus = 0;
		devfn = 0; /* special case: bridge controller itself */
	}

	/* Select bus */
	spin_lock_irqsave(&grpci2_dev_lock, flags);
	REGSTORE(priv->regs->ctrl, (REGLOAD(priv->regs->ctrl) & ~(0xff << 16)) |
				   (bus << 16));
	spin_unlock_irqrestore(&grpci2_dev_lock, flags);

	/* clear old status */
	REGSTORE(priv->regs->sts_cap, (STS_CFGERR | STS_CFGERRVALID));

	pci_conf = (unsigned int *) (priv->pci_conf |
						(devfn << 8) | (where & 0xfc));
	LEON3_BYPASS_STORE_PA(pci_conf, swab32(val));

	/* Wait until GRPCI2 signals that CFG access is done, it should be
	 * done instantaneously unless a DMA operation is ongoing...
	 */
	while ((REGLOAD(priv->regs->sts_cap) & STS_CFGERRVALID) == 0)
		;

	return 0;
}