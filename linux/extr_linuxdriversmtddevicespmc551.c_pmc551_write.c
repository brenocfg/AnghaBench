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
typedef  size_t u32 ;
struct mypriv {int asize; } ;
struct mtd_info {size_t size; struct mypriv* priv; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  pmc551_point (struct mtd_info*,size_t,size_t,size_t*,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmc551_write(struct mtd_info *mtd, loff_t to, size_t len,
			size_t * retlen, const u_char * buf)
{
	struct mypriv *priv = mtd->priv;
	u32 soff_hi, soff_lo;	/* start address offset hi/lo */
	u32 eoff_hi, eoff_lo;	/* end address offset hi/lo */
	unsigned long end;
	u_char *ptr;
	const u_char *copyfrom = buf;

#ifdef CONFIG_MTD_PMC551_DEBUG
	printk(KERN_DEBUG "pmc551_write(pos:%ld, len:%ld) asize:%ld\n",
		(long)to, (long)len, (long)priv->asize);
#endif

	end = to + len - 1;
	soff_hi = to & ~(priv->asize - 1);
	eoff_hi = end & ~(priv->asize - 1);
	soff_lo = to & (priv->asize - 1);
	eoff_lo = end & (priv->asize - 1);

	pmc551_point(mtd, to, len, retlen, (void **)&ptr, NULL);

	if (soff_hi == eoff_hi) {
		/* The whole thing fits within one access, so just one shot
		   will do it. */
		memcpy(ptr, copyfrom, len);
		copyfrom += len;
	} else {
		/* We have to do multiple writes to get all the data
		   written. */
		while (soff_hi != eoff_hi) {
#ifdef CONFIG_MTD_PMC551_DEBUG
			printk(KERN_DEBUG "pmc551_write() soff_hi: %ld, "
				"eoff_hi: %ld\n", (long)soff_hi, (long)eoff_hi);
#endif
			memcpy(ptr, copyfrom, priv->asize);
			copyfrom += priv->asize;
			if (soff_hi >= mtd->size) {
				goto out;
			}
			soff_hi += priv->asize;
			pmc551_point(mtd, soff_hi, priv->asize, retlen,
				     (void **)&ptr, NULL);
		}
		memcpy(ptr, copyfrom, eoff_lo);
		copyfrom += eoff_lo;
	}

      out:
#ifdef CONFIG_MTD_PMC551_DEBUG
	printk(KERN_DEBUG "pmc551_write() done\n");
#endif
	*retlen = copyfrom - buf;
	return 0;
}