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
struct ice_ctx_ele {int offset; int lsb; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  dest_byte ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void
ice_write_byte(u8 *src_ctx, u8 *dest_ctx, const struct ice_ctx_ele *ce_info)
{
	u8 src_byte, dest_byte, mask;
	u8 *from, *dest;
	u16 shift_width;

	/* copy from the next struct field */
	from = src_ctx + ce_info->offset;

	/* prepare the bits and mask */
	shift_width = ce_info->lsb % 8;
	mask = (u8)(BIT(ce_info->width) - 1);

	src_byte = *from;
	src_byte &= mask;

	/* shift to correct alignment */
	mask <<= shift_width;
	src_byte <<= shift_width;

	/* get the current bits from the target bit string */
	dest = dest_ctx + (ce_info->lsb / 8);

	memcpy(&dest_byte, dest, sizeof(dest_byte));

	dest_byte &= ~mask;	/* get the bits not changing */
	dest_byte |= src_byte;	/* add in the new bits */

	/* put it all back */
	memcpy(dest, &dest_byte, sizeof(dest_byte));
}