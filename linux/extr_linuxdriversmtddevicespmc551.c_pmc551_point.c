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
typedef  int u32 ;
struct mypriv {int asize; int curr_map0; int base_map0; void* start; int /*<<< orphan*/  dev; } ;
struct mtd_info {struct mypriv* priv; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMC551_PCI_MEM_MAP0 ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pmc551_point(struct mtd_info *mtd, loff_t from, size_t len,
			size_t *retlen, void **virt, resource_size_t *phys)
{
	struct mypriv *priv = mtd->priv;
	u32 soff_hi;
	u32 soff_lo;

#ifdef CONFIG_MTD_PMC551_DEBUG
	printk(KERN_DEBUG "pmc551_point(%ld, %ld)\n", (long)from, (long)len);
#endif

	soff_hi = from & ~(priv->asize - 1);
	soff_lo = from & (priv->asize - 1);

	/* Cheap hack optimization */
	if (priv->curr_map0 != from) {
		pci_write_config_dword(priv->dev, PMC551_PCI_MEM_MAP0,
					(priv->base_map0 | soff_hi));
		priv->curr_map0 = soff_hi;
	}

	*virt = priv->start + soff_lo;
	*retlen = len;
	return 0;
}