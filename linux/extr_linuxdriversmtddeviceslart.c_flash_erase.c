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
struct mtd_info {int numeraseregions; TYPE_1__* eraseregions; } ;
struct erase_info {int addr; int len; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {int offset; int erasesize; int numblocks; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  erase_block (scalar_t__) ; 

__attribute__((used)) static int flash_erase (struct mtd_info *mtd,struct erase_info *instr)
{
   __u32 addr,len;
   int i,first;

#ifdef LART_DEBUG
   printk (KERN_DEBUG "%s(addr = 0x%.8x, len = %d)\n", __func__, instr->addr, instr->len);
#endif

   /*
	* check that both start and end of the requested erase are
	* aligned with the erasesize at the appropriate addresses.
	*
	* skip all erase regions which are ended before the start of
	* the requested erase. Actually, to save on the calculations,
	* we skip to the first erase region which starts after the
	* start of the requested erase, and then go back one.
	*/
   for (i = 0; i < mtd->numeraseregions && instr->addr >= mtd->eraseregions[i].offset; i++) ;
   i--;

   /*
	* ok, now i is pointing at the erase region in which this
	* erase request starts. Check the start of the requested
	* erase range is aligned with the erase size which is in
	* effect here.
	*/
   if (i < 0 || (instr->addr & (mtd->eraseregions[i].erasesize - 1)))
      return -EINVAL;

   /* Remember the erase region we start on */
   first = i;

   /*
	* next, check that the end of the requested erase is aligned
	* with the erase region at that address.
	*
	* as before, drop back one to point at the region in which
	* the address actually falls
	*/
   for (; i < mtd->numeraseregions && instr->addr + instr->len >= mtd->eraseregions[i].offset; i++) ;
   i--;

   /* is the end aligned on a block boundary? */
   if (i < 0 || ((instr->addr + instr->len) & (mtd->eraseregions[i].erasesize - 1)))
      return -EINVAL;

   addr = instr->addr;
   len = instr->len;

   i = first;

   /* now erase those blocks */
   while (len)
	 {
		if (!erase_block (addr))
			 return (-EIO);

		addr += mtd->eraseregions[i].erasesize;
		len -= mtd->eraseregions[i].erasesize;

		if (addr == mtd->eraseregions[i].offset + (mtd->eraseregions[i].erasesize * mtd->eraseregions[i].numblocks)) i++;
	 }

   return (0);
}