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
typedef  int u32 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int HW_ATL_UCP_0X370_REG ; 
 int __swab32 (int) ; 
 int aq_hw_read_reg (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int,unsigned int) ; 
 int /*<<< orphan*/  ether_addr_copy (int*,int*) ; 
 int /*<<< orphan*/  get_random_bytes (unsigned int*,int) ; 
 int hw_atl_utils_fw_downld_dwords (struct aq_hw_s*,int,int*,int /*<<< orphan*/ ) ; 

int hw_atl_utils_get_mac_permanent(struct aq_hw_s *self,
				   u8 *mac)
{
	int err = 0;
	u32 h = 0U;
	u32 l = 0U;
	u32 mac_addr[2];

	if (!aq_hw_read_reg(self, HW_ATL_UCP_0X370_REG)) {
		unsigned int rnd = 0;
		unsigned int ucp_0x370 = 0;

		get_random_bytes(&rnd, sizeof(unsigned int));

		ucp_0x370 = 0x02020202 | (0xFEFEFEFE & rnd);
		aq_hw_write_reg(self, HW_ATL_UCP_0X370_REG, ucp_0x370);
	}

	err = hw_atl_utils_fw_downld_dwords(self,
					    aq_hw_read_reg(self, 0x00000374U) +
					    (40U * 4U),
					    mac_addr,
					    ARRAY_SIZE(mac_addr));
	if (err < 0) {
		mac_addr[0] = 0U;
		mac_addr[1] = 0U;
		err = 0;
	} else {
		mac_addr[0] = __swab32(mac_addr[0]);
		mac_addr[1] = __swab32(mac_addr[1]);
	}

	ether_addr_copy(mac, (u8 *)mac_addr);

	if ((mac[0] & 0x01U) || ((mac[0] | mac[1] | mac[2]) == 0x00U)) {
		/* chip revision */
		l = 0xE3000000U |
		    (0xFFFFU & aq_hw_read_reg(self, HW_ATL_UCP_0X370_REG)) |
		    (0x00 << 16);
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