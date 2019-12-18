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
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  genesis_mac_intr (struct skge_hw*,int) ; 
 scalar_t__ is_genesis (struct skge_hw*) ; 
 int /*<<< orphan*/  yukon_mac_intr (struct skge_hw*,int) ; 

__attribute__((used)) static void skge_mac_intr(struct skge_hw *hw, int port)
{
	if (is_genesis(hw))
		genesis_mac_intr(hw, port);
	else
		yukon_mac_intr(hw, port);
}