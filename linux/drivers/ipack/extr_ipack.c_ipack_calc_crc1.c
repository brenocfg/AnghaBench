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
struct ipack_device {unsigned int id_avail; int* id; } ;

/* Variables and functions */
 int ipack_crc_byte (int,int) ; 

__attribute__((used)) static u8 ipack_calc_crc1(struct ipack_device *dev)
{
	u8 c;
	u16 crc;
	unsigned int i;

	crc = 0xffff;
	for (i = 0; i < dev->id_avail; i++) {
		c = (i != 11) ? dev->id[i] : 0;
		crc = ipack_crc_byte(crc, c);
	}
	crc = ~crc;
	return crc & 0xff;
}