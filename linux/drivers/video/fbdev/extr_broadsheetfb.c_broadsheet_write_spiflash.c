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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int broadsheet_spiflash_rewrite_sector (struct broadsheetfb_par*,int,int,int,int /*<<< orphan*/  const*) ; 
 int min (int,int) ; 
 int roundup (int,int) ; 

__attribute__((used)) static int broadsheet_write_spiflash(struct broadsheetfb_par *par, u32 wfm_addr,
				const u8 *wfm, int bytecount, int flash_type)
{
	int sector_size;
	int err;
	int cur_addr;
	int writecount;
	int maxlen;
	int offset = 0;

	switch (flash_type) {
	case 0x10:
		sector_size = 32*1024;
		break;
	case 0x11:
	default:
		sector_size = 64*1024;
		break;
	}

	while (bytecount) {
		cur_addr = wfm_addr + offset;
		maxlen = roundup(cur_addr, sector_size) - cur_addr;
		writecount = min(bytecount, maxlen);

		err = broadsheet_spiflash_rewrite_sector(par, sector_size,
				cur_addr, writecount, wfm + offset);
		if (err)
			return err;

		offset += writecount;
		bytecount -= writecount;
	}

	return 0;
}