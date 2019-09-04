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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EECD ; 
 int /*<<< orphan*/  E1000_EECD_REQ ; 
 int /*<<< orphan*/  e1000_stop_nvm (struct e1000_hw*) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void igb_release_nvm(struct e1000_hw *hw)
{
	u32 eecd;

	e1000_stop_nvm(hw);

	eecd = rd32(E1000_EECD);
	eecd &= ~E1000_EECD_REQ;
	wr32(E1000_EECD, eecd);
}