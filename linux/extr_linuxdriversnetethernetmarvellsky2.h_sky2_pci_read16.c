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
typedef  int /*<<< orphan*/  u16 ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 unsigned int Y2_CFG_SPC ; 
 int /*<<< orphan*/  sky2_read16 (struct sky2_hw const*,unsigned int) ; 

__attribute__((used)) static inline u16 sky2_pci_read16(const struct sky2_hw *hw, unsigned reg)
{
	return sky2_read16(hw, Y2_CFG_SPC + reg);
}