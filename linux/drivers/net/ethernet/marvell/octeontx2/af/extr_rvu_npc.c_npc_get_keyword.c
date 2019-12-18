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
struct mcam_entry {int* kw; int* kw_mask; } ;

/* Variables and functions */
 int CAM_MASK (int) ; 

__attribute__((used)) static void npc_get_keyword(struct mcam_entry *entry, int idx,
			    u64 *cam0, u64 *cam1)
{
	u64 kw_mask = 0x00;

#define CAM_MASK(n)	(BIT_ULL(n) - 1)

	/* 0, 2, 4, 6 indices refer to BANKX_CAMX_W0 and
	 * 1, 3, 5, 7 indices refer to BANKX_CAMX_W1.
	 *
	 * Also, only 48 bits of BANKX_CAMX_W1 are valid.
	 */
	switch (idx) {
	case 0:
		/* BANK(X)_CAM_W0<63:0> = MCAM_KEY[KW0]<63:0> */
		*cam1 = entry->kw[0];
		kw_mask = entry->kw_mask[0];
		break;
	case 1:
		/* BANK(X)_CAM_W1<47:0> = MCAM_KEY[KW1]<47:0> */
		*cam1 = entry->kw[1] & CAM_MASK(48);
		kw_mask = entry->kw_mask[1] & CAM_MASK(48);
		break;
	case 2:
		/* BANK(X + 1)_CAM_W0<15:0> = MCAM_KEY[KW1]<63:48>
		 * BANK(X + 1)_CAM_W0<63:16> = MCAM_KEY[KW2]<47:0>
		 */
		*cam1 = (entry->kw[1] >> 48) & CAM_MASK(16);
		*cam1 |= ((entry->kw[2] & CAM_MASK(48)) << 16);
		kw_mask = (entry->kw_mask[1] >> 48) & CAM_MASK(16);
		kw_mask |= ((entry->kw_mask[2] & CAM_MASK(48)) << 16);
		break;
	case 3:
		/* BANK(X + 1)_CAM_W1<15:0> = MCAM_KEY[KW2]<63:48>
		 * BANK(X + 1)_CAM_W1<47:16> = MCAM_KEY[KW3]<31:0>
		 */
		*cam1 = (entry->kw[2] >> 48) & CAM_MASK(16);
		*cam1 |= ((entry->kw[3] & CAM_MASK(32)) << 16);
		kw_mask = (entry->kw_mask[2] >> 48) & CAM_MASK(16);
		kw_mask |= ((entry->kw_mask[3] & CAM_MASK(32)) << 16);
		break;
	case 4:
		/* BANK(X + 2)_CAM_W0<31:0> = MCAM_KEY[KW3]<63:32>
		 * BANK(X + 2)_CAM_W0<63:32> = MCAM_KEY[KW4]<31:0>
		 */
		*cam1 = (entry->kw[3] >> 32) & CAM_MASK(32);
		*cam1 |= ((entry->kw[4] & CAM_MASK(32)) << 32);
		kw_mask = (entry->kw_mask[3] >> 32) & CAM_MASK(32);
		kw_mask |= ((entry->kw_mask[4] & CAM_MASK(32)) << 32);
		break;
	case 5:
		/* BANK(X + 2)_CAM_W1<31:0> = MCAM_KEY[KW4]<63:32>
		 * BANK(X + 2)_CAM_W1<47:32> = MCAM_KEY[KW5]<15:0>
		 */
		*cam1 = (entry->kw[4] >> 32) & CAM_MASK(32);
		*cam1 |= ((entry->kw[5] & CAM_MASK(16)) << 32);
		kw_mask = (entry->kw_mask[4] >> 32) & CAM_MASK(32);
		kw_mask |= ((entry->kw_mask[5] & CAM_MASK(16)) << 32);
		break;
	case 6:
		/* BANK(X + 3)_CAM_W0<47:0> = MCAM_KEY[KW5]<63:16>
		 * BANK(X + 3)_CAM_W0<63:48> = MCAM_KEY[KW6]<15:0>
		 */
		*cam1 = (entry->kw[5] >> 16) & CAM_MASK(48);
		*cam1 |= ((entry->kw[6] & CAM_MASK(16)) << 48);
		kw_mask = (entry->kw_mask[5] >> 16) & CAM_MASK(48);
		kw_mask |= ((entry->kw_mask[6] & CAM_MASK(16)) << 48);
		break;
	case 7:
		/* BANK(X + 3)_CAM_W1<47:0> = MCAM_KEY[KW6]<63:16> */
		*cam1 = (entry->kw[6] >> 16) & CAM_MASK(48);
		kw_mask = (entry->kw_mask[6] >> 16) & CAM_MASK(48);
		break;
	}

	*cam1 &= kw_mask;
	*cam0 = ~*cam1 & kw_mask;
}