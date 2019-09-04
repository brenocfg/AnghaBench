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
typedef  int u_char ;
struct mtd_info {int dummy; } ;
typedef  int loff_t ;
typedef  int __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int BUSWIDTH ; 
 int EIO ; 
 int /*<<< orphan*/  write_dword (int,int) ; 

__attribute__((used)) static int flash_write (struct mtd_info *mtd,loff_t to,size_t len,size_t *retlen,const u_char *buf)
{
   __u8 tmp[4];
   int i,n;

#ifdef LART_DEBUG
   printk (KERN_DEBUG "%s(to = 0x%.8x, len = %d)\n", __func__, (__u32)to, len);
#endif

   /* sanity checks */
   if (!len) return (0);

   /* first, we write a 0xFF.... padded byte until we reach a dword boundary */
   if (to & (BUSWIDTH - 1))
	 {
		__u32 aligned = to & ~(BUSWIDTH - 1);
		int gap = to - aligned;

		i = n = 0;

		while (gap--) tmp[i++] = 0xFF;
		while (len && i < BUSWIDTH) tmp[i++] = buf[n++], len--;
		while (i < BUSWIDTH) tmp[i++] = 0xFF;

		if (!write_dword (aligned,*((__u32 *) tmp))) return (-EIO);

		to += n;
		buf += n;
		*retlen += n;
	 }

   /* now we write dwords until we reach a non-dword boundary */
   while (len >= BUSWIDTH)
	 {
		if (!write_dword (to,*((__u32 *) buf))) return (-EIO);

		to += BUSWIDTH;
		buf += BUSWIDTH;
		*retlen += BUSWIDTH;
		len -= BUSWIDTH;
	 }

   /* top up the last unaligned bytes, padded with 0xFF.... */
   if (len & (BUSWIDTH - 1))
	 {
		i = n = 0;

		while (len--) tmp[i++] = buf[n++];
		while (i < BUSWIDTH) tmp[i++] = 0xFF;

		if (!write_dword (to,*((__u32 *) tmp))) return (-EIO);

		*retlen += n;
	 }

   return (0);
}