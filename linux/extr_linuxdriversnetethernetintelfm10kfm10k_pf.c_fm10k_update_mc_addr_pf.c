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
typedef  int /*<<< orphan*/  u16 ;
struct fm10k_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int /*<<< orphan*/  fm10k_update_xc_addr_pf (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static s32 fm10k_update_mc_addr_pf(struct fm10k_hw *hw, u16 glort,
				   const u8 *mac, u16 vid, bool add)
{
	/* verify multicast address is valid */
	if (!is_multicast_ether_addr(mac))
		return FM10K_ERR_PARAM;

	return fm10k_update_xc_addr_pf(hw, glort, mac, vid, add, 0);
}