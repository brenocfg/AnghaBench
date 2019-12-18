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
typedef  enum romcode_write { ____Placeholder_romcode_write } romcode_write ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PRCM_ROMCODE_A2P ; 
 int RDY_2_DS ; 
 int RDY_2_XP70_RST ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

int prcmu_set_rc_a2p(enum romcode_write val)
{
	if (val < RDY_2_DS || val > RDY_2_XP70_RST)
		return -EINVAL;
	writeb(val, (tcdm_base + PRCM_ROMCODE_A2P));
	return 0;
}