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
typedef  scalar_t__ u16 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_MAP_MAX_SIZE ; 
 int PGPKT_DATA_SIZE ; 
 scalar_t__ efuse_is_empty (struct _adapter*,int*) ; 
 int r8712_efuse_pg_packet_read (struct _adapter*,int,int*) ; 

u8 r8712_efuse_map_read(struct _adapter *adapter, u16 addr, u16 cnts, u8 *data)
{
	u8 offset, ret = true;
	u8 pktdata[PGPKT_DATA_SIZE];
	int i, idx;

	if ((addr + cnts) > EFUSE_MAP_MAX_SIZE)
		return false;
	if (efuse_is_empty(adapter, &offset) && offset) {
		for (i = 0; i < cnts; i++)
			data[i] = 0xFF;
		return ret;
	}
	offset = (addr >> 3) & 0xF;
	ret = r8712_efuse_pg_packet_read(adapter, offset, pktdata);
	i = addr & 0x7;	/* pktdata index */
	idx = 0;	/* data index */

	do {
		for (; i < PGPKT_DATA_SIZE; i++) {
			data[idx++] = pktdata[i];
			if (idx == cnts)
				return ret;
		}
		offset++;
		if (!r8712_efuse_pg_packet_read(adapter, offset, pktdata))
			ret = false;
		i = 0;
	} while (1);
	return ret;
}