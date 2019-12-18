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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct sh_eth_private {scalar_t__ tsu_addr; } ;

/* Variables and functions */
 scalar_t__ SH_ETH_OFFSET_INVALID ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sh_eth_tsu_get_offset (struct sh_eth_private*,int) ; 

__attribute__((used)) static void sh_eth_tsu_write(struct sh_eth_private *mdp, u32 data,
			     int enum_index)
{
	u16 offset = sh_eth_tsu_get_offset(mdp, enum_index);

	if (WARN_ON(offset == SH_ETH_OFFSET_INVALID))
		return;

	iowrite32(data, mdp->tsu_addr + offset);
}