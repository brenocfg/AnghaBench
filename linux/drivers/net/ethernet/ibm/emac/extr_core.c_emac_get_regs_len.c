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
struct emac_regs {int dummy; } ;
struct emac_instance {int dummy; } ;
struct emac_ethtool_regs_subhdr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int emac_get_regs_len(struct emac_instance *dev)
{
		return sizeof(struct emac_ethtool_regs_subhdr) +
			sizeof(struct emac_regs);
}