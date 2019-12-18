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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ ETHTOOL_FEC_OFF_BIT ; 
 scalar_t__ ETHTOOL_LINK_MODE_FEC_NONE_BIT ; 
 int /*<<< orphan*/  find_first_bit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u32 ethtool_fec2ethtool_caps(u_long ethtool_fec_code)
{
	u32 offset;

	offset = find_first_bit(&ethtool_fec_code, sizeof(u32));
	offset -= ETHTOOL_FEC_OFF_BIT;
	offset += ETHTOOL_LINK_MODE_FEC_NONE_BIT;

	return offset;
}