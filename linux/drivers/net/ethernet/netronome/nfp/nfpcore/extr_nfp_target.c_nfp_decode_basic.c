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
typedef  int u64 ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int EINVAL ; 
 int NFP_CPP_TARGET_CT_XPB ; 
 int NFP_CPP_TARGET_MU ; 

__attribute__((used)) static int nfp_decode_basic(u64 addr, int *dest_island, int cpp_tgt,
			    int mode, bool addr40, int isld1, int isld0)
{
	int iid_lsb, idx_lsb;

	/* This function doesn't handle MU or CTXBP */
	if (cpp_tgt == NFP_CPP_TARGET_MU || cpp_tgt == NFP_CPP_TARGET_CT_XPB)
		return -EINVAL;

	switch (mode) {
	case 0:
		/* For VQDR, in this mode for 32-bit addressing
		 * it would be islands 0, 16, 32 and 48 depending on channel
		 * and upper address bits.
		 * Since those are not all valid islands, most decode
		 * cases would result in bad island IDs, but we do them
		 * anyway since this is decoding an address that is already
		 * assumed to be used as-is to get to sram.
		 */
		iid_lsb = addr40 ? 34 : 26;
		*dest_island = (addr >> iid_lsb) & 0x3F;
		return 0;
	case 1:
		/* For VQDR 32-bit, this would decode as:
		 * Channel 0: island#0
		 * Channel 1: island#0
		 * Channel 2: island#1
		 * Channel 3: island#1
		 * That would be valid as long as both islands
		 * have VQDR. Let's allow this.
		 */
		idx_lsb = addr40 ? 39 : 31;
		if (addr & BIT_ULL(idx_lsb))
			*dest_island = isld1;
		else
			*dest_island = isld0;

		return 0;
	case 2:
		/* For VQDR 32-bit:
		 * Channel 0: (island#0 | 0)
		 * Channel 1: (island#0 | 1)
		 * Channel 2: (island#1 | 0)
		 * Channel 3: (island#1 | 1)
		 *
		 * Make sure we compare against isldN values
		 * by clearing the LSB.
		 * This is what the silicon does.
		 */
		isld0 &= ~1;
		isld1 &= ~1;

		idx_lsb = addr40 ? 39 : 31;
		iid_lsb = idx_lsb - 1;

		if (addr & BIT_ULL(idx_lsb))
			*dest_island = isld1 | (int)((addr >> iid_lsb) & 1);
		else
			*dest_island = isld0 | (int)((addr >> iid_lsb) & 1);

		return 0;
	case 3:
		/* In this mode the data address starts to affect the island ID
		 * so rather not allow it. In some really specific case
		 * one could use this to send the upper half of the
		 * VQDR channel to another MU, but this is getting very
		 * specific.
		 * However, as above for mode 0, this is the decoder
		 * and the caller should validate the resulting IID.
		 * This blindly does what the silicon would do.
		 */
		isld0 &= ~3;
		isld1 &= ~3;

		idx_lsb = addr40 ? 39 : 31;
		iid_lsb = idx_lsb - 2;

		if (addr & BIT_ULL(idx_lsb))
			*dest_island = isld1 | (int)((addr >> iid_lsb) & 3);
		else
			*dest_island = isld0 | (int)((addr >> iid_lsb) & 3);

		return 0;
	default:
		return -EINVAL;
	}
}