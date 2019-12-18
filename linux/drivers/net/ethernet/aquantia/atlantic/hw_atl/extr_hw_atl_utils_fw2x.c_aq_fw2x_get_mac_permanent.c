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
typedef  scalar_t__ u32 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  HW_ATL_FW2X_MPI_EFUSE_ADDR ; 
 scalar_t__ __swab32 (scalar_t__) ; 
 scalar_t__ aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int*,int*) ; 
 int /*<<< orphan*/  get_random_bytes (unsigned int*,int) ; 
 int hw_atl_utils_fw_downld_dwords (struct aq_hw_s*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aq_fw2x_get_mac_permanent(struct aq_hw_s *self, u8 *mac)
{
	int err = 0;
	u32 h = 0U;
	u32 l = 0U;
	u32 mac_addr[2] = { 0 };
	u32 efuse_addr = aq_hw_read_reg(self, HW_ATL_FW2X_MPI_EFUSE_ADDR);

	if (efuse_addr != 0) {
		err = hw_atl_utils_fw_downld_dwords(self,
						    efuse_addr + (40U * 4U),
						    mac_addr,
						    ARRAY_SIZE(mac_addr));
		if (err)
			return err;
		mac_addr[0] = __swab32(mac_addr[0]);
		mac_addr[1] = __swab32(mac_addr[1]);
	}

	ether_addr_copy(mac, (u8 *)mac_addr);

	if ((mac[0] & 0x01U) || ((mac[0] | mac[1] | mac[2]) == 0x00U)) {
		unsigned int rnd = 0;

		get_random_bytes(&rnd, sizeof(unsigned int));

		l = 0xE3000000U | (0xFFFFU & rnd) | (0x00 << 16);
		h = 0x8001300EU;

		mac[5] = (u8)(0xFFU & l);
		l >>= 8;
		mac[4] = (u8)(0xFFU & l);
		l >>= 8;
		mac[3] = (u8)(0xFFU & l);
		l >>= 8;
		mac[2] = (u8)(0xFFU & l);
		mac[1] = (u8)(0xFFU & h);
		h >>= 8;
		mac[0] = (u8)(0xFFU & h);
	}
	return err;
}