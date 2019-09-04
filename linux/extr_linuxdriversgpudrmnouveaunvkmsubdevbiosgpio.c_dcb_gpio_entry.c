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
typedef  int u16 ;
struct nvkm_bios {int dummy; } ;

/* Variables and functions */
 int dcb_gpio_table (struct nvkm_bios*,int*,int*,int*,int*) ; 
 int dcb_xpio_table (struct nvkm_bios*,int,int*,int*,int*,int*) ; 

u16
dcb_gpio_entry(struct nvkm_bios *bios, int idx, int ent, u8 *ver, u8 *len)
{
	u8  hdr, cnt, xver; /* use gpio version for xpio entry parsing */
	u16 gpio;

	if (!idx--)
		gpio = dcb_gpio_table(bios, ver, &hdr, &cnt, len);
	else
		gpio = dcb_xpio_table(bios, idx, &xver, &hdr, &cnt, len);

	if (gpio && ent < cnt)
		return gpio + hdr + (ent * *len);

	return 0x0000;
}