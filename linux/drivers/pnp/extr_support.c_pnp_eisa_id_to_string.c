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

/* Variables and functions */
 int be32_to_cpu (int) ; 
 char hex_asc_hi (int) ; 
 char hex_asc_lo (int) ; 

void pnp_eisa_id_to_string(u32 id, char *str)
{
	id = be32_to_cpu(id);

	/*
	 * According to the specs, the first three characters are five-bit
	 * compressed ASCII, and the left-over high order bit should be zero.
	 * However, the Linux ISAPNP code historically used six bits for the
	 * first character, and there seem to be IDs that depend on that,
	 * e.g., "nEC8241" in the Linux 8250_pnp serial driver and the
	 * FreeBSD sys/pc98/cbus/sio_cbus.c driver.
	 */
	str[0] = 'A' + ((id >> 26) & 0x3f) - 1;
	str[1] = 'A' + ((id >> 21) & 0x1f) - 1;
	str[2] = 'A' + ((id >> 16) & 0x1f) - 1;
	str[3] = hex_asc_hi(id >> 8);
	str[4] = hex_asc_lo(id >> 8);
	str[5] = hex_asc_hi(id);
	str[6] = hex_asc_lo(id);
	str[7] = '\0';
}