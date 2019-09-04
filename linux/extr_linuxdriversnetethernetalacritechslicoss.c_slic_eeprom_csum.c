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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static u16 slic_eeprom_csum(unsigned char *eeprom, unsigned int len)
{
	unsigned char *ptr = eeprom;
	u32 csum = 0;
	__le16 data;

	while (len > 1) {
		memcpy(&data, ptr, sizeof(data));
		csum += le16_to_cpu(data);
		ptr += 2;
		len -= 2;
	}
	if (len > 0)
		csum += *(u8 *)ptr;
	while (csum >> 16)
		csum = (csum & 0xFFFF) + ((csum >> 16) & 0xFFFF);
	return ~csum;
}