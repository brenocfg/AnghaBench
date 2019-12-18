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
typedef  int u8 ;
typedef  int u32 ;
typedef  void* u16 ;
struct lpc32xx_udc {int /*<<< orphan*/  udp_baseaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_RXDATA (int /*<<< orphan*/ ) ; 
 void* readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_pop_fifo(struct lpc32xx_udc *udc, u8 *data, u32 bytes)
{
	int n, i, bl;
	u16 *p16;
	u32 *p32, tmp, cbytes;

	/* Use optimal data transfer method based on source address and size */
	switch (((uintptr_t) data) & 0x3) {
	case 0: /* 32-bit aligned */
		p32 = (u32 *) data;
		cbytes = (bytes & ~0x3);

		/* Copy 32-bit aligned data first */
		for (n = 0; n < cbytes; n += 4)
			*p32++ = readl(USBD_RXDATA(udc->udp_baseaddr));

		/* Handle any remaining bytes */
		bl = bytes - cbytes;
		if (bl) {
			tmp = readl(USBD_RXDATA(udc->udp_baseaddr));
			for (n = 0; n < bl; n++)
				data[cbytes + n] = ((tmp >> (n * 8)) & 0xFF);

		}
		break;

	case 1: /* 8-bit aligned */
	case 3:
		/* Each byte has to be handled independently */
		for (n = 0; n < bytes; n += 4) {
			tmp = readl(USBD_RXDATA(udc->udp_baseaddr));

			bl = bytes - n;
			if (bl > 4)
				bl = 4;

			for (i = 0; i < bl; i++)
				data[n + i] = (u8) ((tmp >> (i * 8)) & 0xFF);
		}
		break;

	case 2: /* 16-bit aligned */
		p16 = (u16 *) data;
		cbytes = (bytes & ~0x3);

		/* Copy 32-bit sized objects first with 16-bit alignment */
		for (n = 0; n < cbytes; n += 4) {
			tmp = readl(USBD_RXDATA(udc->udp_baseaddr));
			*p16++ = (u16)(tmp & 0xFFFF);
			*p16++ = (u16)((tmp >> 16) & 0xFFFF);
		}

		/* Handle any remaining bytes */
		bl = bytes - cbytes;
		if (bl) {
			tmp = readl(USBD_RXDATA(udc->udp_baseaddr));
			for (n = 0; n < bl; n++)
				data[cbytes + n] = ((tmp >> (n * 8)) & 0xFF);
		}
		break;
	}
}