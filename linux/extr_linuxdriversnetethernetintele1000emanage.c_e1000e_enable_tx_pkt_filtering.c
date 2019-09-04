#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* check_mng_mode ) (struct e1000_hw*) ;} ;
struct TYPE_4__ {int tx_pkt_filtering; TYPE_1__ ops; } ;
struct e1000_host_mng_dhcp_cookie {scalar_t__ checksum; scalar_t__ signature; int status; } ;
struct e1000_hw {TYPE_2__ mac; struct e1000_host_mng_dhcp_cookie mng_cookie; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_HOST_IF ; 
 scalar_t__ E1000_IAMT_SIGNATURE ; 
 int E1000_MNG_DHCP_COOKIE_LENGTH ; 
 int E1000_MNG_DHCP_COOKIE_OFFSET ; 
 int E1000_MNG_DHCP_COOKIE_STATUS_PARSING ; 
 int E1000_READ_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_calculate_checksum (int*,int) ; 
 scalar_t__ e1000_mng_enable_host_if (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

bool e1000e_enable_tx_pkt_filtering(struct e1000_hw *hw)
{
	struct e1000_host_mng_dhcp_cookie *hdr = &hw->mng_cookie;
	u32 *buffer = (u32 *)&hw->mng_cookie;
	u32 offset;
	s32 ret_val, hdr_csum, csum;
	u8 i, len;

	hw->mac.tx_pkt_filtering = true;

	/* No manageability, no filtering */
	if (!hw->mac.ops.check_mng_mode(hw)) {
		hw->mac.tx_pkt_filtering = false;
		return hw->mac.tx_pkt_filtering;
	}

	/* If we can't read from the host interface for whatever
	 * reason, disable filtering.
	 */
	ret_val = e1000_mng_enable_host_if(hw);
	if (ret_val) {
		hw->mac.tx_pkt_filtering = false;
		return hw->mac.tx_pkt_filtering;
	}

	/* Read in the header.  Length and offset are in dwords. */
	len = E1000_MNG_DHCP_COOKIE_LENGTH >> 2;
	offset = E1000_MNG_DHCP_COOKIE_OFFSET >> 2;
	for (i = 0; i < len; i++)
		*(buffer + i) = E1000_READ_REG_ARRAY(hw, E1000_HOST_IF,
						     offset + i);
	hdr_csum = hdr->checksum;
	hdr->checksum = 0;
	csum = e1000_calculate_checksum((u8 *)hdr,
					E1000_MNG_DHCP_COOKIE_LENGTH);
	/* If either the checksums or signature don't match, then
	 * the cookie area isn't considered valid, in which case we
	 * take the safe route of assuming Tx filtering is enabled.
	 */
	if ((hdr_csum != csum) || (hdr->signature != E1000_IAMT_SIGNATURE)) {
		hw->mac.tx_pkt_filtering = true;
		return hw->mac.tx_pkt_filtering;
	}

	/* Cookie area is valid, make the final check for filtering. */
	if (!(hdr->status & E1000_MNG_DHCP_COOKIE_STATUS_PARSING))
		hw->mac.tx_pkt_filtering = false;

	return hw->mac.tx_pkt_filtering;
}