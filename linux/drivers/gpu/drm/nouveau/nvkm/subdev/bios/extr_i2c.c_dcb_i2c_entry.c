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
 int dcb_i2c_table (struct nvkm_bios*,int*,int*,int*,int*) ; 

u16
dcb_i2c_entry(struct nvkm_bios *bios, u8 idx, u8 *ver, u8 *len)
{
	u8  hdr, cnt;
	u16 i2c = dcb_i2c_table(bios, ver, &hdr, &cnt, len);
	if (i2c && idx < cnt)
		return i2c + hdr + (idx * *len);
	return 0x0000;
}