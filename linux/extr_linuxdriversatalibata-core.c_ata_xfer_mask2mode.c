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
struct ata_xfer_ent {int shift; int bits; int base; } ;

/* Variables and functions */
 struct ata_xfer_ent* ata_xfer_tbl ; 
 int fls (unsigned long) ; 

u8 ata_xfer_mask2mode(unsigned long xfer_mask)
{
	int highbit = fls(xfer_mask) - 1;
	const struct ata_xfer_ent *ent;

	for (ent = ata_xfer_tbl; ent->shift >= 0; ent++)
		if (highbit >= ent->shift && highbit < ent->shift + ent->bits)
			return ent->base + highbit - ent->shift;
	return 0xff;
}