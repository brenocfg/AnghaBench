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

/* Variables and functions */
 int /*<<< orphan*/  __ETHTOOL_DECLARE_LINK_MODE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_and (unsigned long*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_or (unsigned long*,unsigned long*,unsigned long const*) ; 
 int /*<<< orphan*/  linkmode_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask ; 
 int /*<<< orphan*/  phylink_set_port_modes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phylink_merge_link_mode(unsigned long *dst, const unsigned long *b)
{
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask);

	linkmode_zero(mask);
	phylink_set_port_modes(mask);

	linkmode_and(dst, dst, mask);
	linkmode_or(dst, dst, b);
}