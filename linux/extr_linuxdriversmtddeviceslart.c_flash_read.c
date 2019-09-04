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
struct mtd_info {int dummy; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int BUSWIDTH ; 
 int /*<<< orphan*/  read32 (int) ; 
 void* read8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flash_read (struct mtd_info *mtd,loff_t from,size_t len,size_t *retlen,u_char *buf)
{
#ifdef LART_DEBUG
   printk (KERN_DEBUG "%s(from = 0x%.8x, len = %d)\n", __func__, (__u32)from, len);
#endif

   /* we always read len bytes */
   *retlen = len;

   /* first, we read bytes until we reach a dword boundary */
   if (from & (BUSWIDTH - 1))
	 {
		int gap = BUSWIDTH - (from & (BUSWIDTH - 1));

		while (len && gap--) *buf++ = read8 (from++), len--;
	 }

   /* now we read dwords until we reach a non-dword boundary */
   while (len >= BUSWIDTH)
	 {
		*((__u32 *) buf) = read32 (from);

		buf += BUSWIDTH;
		from += BUSWIDTH;
		len -= BUSWIDTH;
	 }

   /* top up the last unaligned bytes */
   if (len & (BUSWIDTH - 1))
	 while (len--) *buf++ = read8 (from++);

   return (0);
}