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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_vlan_configure (struct bnx2x*,int) ; 

int bnx2x_vlan_reconfigure_vid(struct bnx2x *bp)
{
	/* Don't set rx mode here. Our caller will do it. */
	bnx2x_vlan_configure(bp, false);

	return 0;
}