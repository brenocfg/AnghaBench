#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int in_use; scalar_t__* flowkey; } ;
struct nix_hw {TYPE_1__ flowkey; } ;

/* Variables and functions */
 int ERANGE ; 

__attribute__((used)) static int get_flowkey_alg_idx(struct nix_hw *nix_hw, u32 flow_cfg)
{
	int i;

	/* Scan over exiting algo entries to find a match */
	for (i = 0; i < nix_hw->flowkey.in_use; i++)
		if (nix_hw->flowkey.flowkey[i] == flow_cfg)
			return i;

	return -ERANGE;
}