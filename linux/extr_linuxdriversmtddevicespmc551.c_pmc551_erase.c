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
typedef  int /*<<< orphan*/  u_char ;
typedef  int u32 ;
struct mypriv {int asize; int base_map0; } ;
struct mtd_info {int size; struct mypriv* priv; } ;
struct erase_info {int addr; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pmc551_point (struct mtd_info*,int,int,size_t*,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmc551_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct mypriv *priv = mtd->priv;
	u32 soff_hi, soff_lo;	/* start address offset hi/lo */
	u32 eoff_hi, eoff_lo;	/* end address offset hi/lo */
	unsigned long end;
	u_char *ptr;
	size_t retlen;

#ifdef CONFIG_MTD_PMC551_DEBUG
	printk(KERN_DEBUG "pmc551_erase(pos:%ld, len:%ld)\n", (long)instr->addr,
		(long)instr->len);
#endif

	end = instr->addr + instr->len - 1;
	eoff_hi = end & ~(priv->asize - 1);
	soff_hi = instr->addr & ~(priv->asize - 1);
	eoff_lo = end & (priv->asize - 1);
	soff_lo = instr->addr & (priv->asize - 1);

	pmc551_point(mtd, instr->addr, instr->len, &retlen,
		     (void **)&ptr, NULL);

	if (soff_hi == eoff_hi || mtd->size == priv->asize) {
		/* The whole thing fits within one access, so just one shot
		   will do it. */
		memset(ptr, 0xff, instr->len);
	} else {
		/* We have to do multiple writes to get all the data
		   written. */
		while (soff_hi != eoff_hi) {
#ifdef CONFIG_MTD_PMC551_DEBUG
			printk(KERN_DEBUG "pmc551_erase() soff_hi: %ld, "
				"eoff_hi: %ld\n", (long)soff_hi, (long)eoff_hi);
#endif
			memset(ptr, 0xff, priv->asize);
			if (soff_hi + priv->asize >= mtd->size) {
				goto out;
			}
			soff_hi += priv->asize;
			pmc551_point(mtd, (priv->base_map0 | soff_hi),
				     priv->asize, &retlen,
				     (void **)&ptr, NULL);
		}
		memset(ptr, 0xff, eoff_lo);
	}

      out:
#ifdef CONFIG_MTD_PMC551_DEBUG
	printk(KERN_DEBUG "pmc551_erase() done\n");
#endif

	return 0;
}