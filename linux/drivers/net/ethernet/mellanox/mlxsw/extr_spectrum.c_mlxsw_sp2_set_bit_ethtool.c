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
struct mlxsw_sp2_port_link_mode {int m_ethtool_len; int /*<<< orphan*/ * mask_ethtool; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void
mlxsw_sp2_set_bit_ethtool(const struct mlxsw_sp2_port_link_mode *link_mode,
			  unsigned long *mode)
{
	int i;

	for (i = 0; i < link_mode->m_ethtool_len; i++)
		__set_bit(link_mode->mask_ethtool[i], mode);
}