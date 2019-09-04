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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static s32 e1000_get_phy_cfg_done(struct e1000_hw *hw)
{
	msleep(10);
	return E1000_SUCCESS;
}