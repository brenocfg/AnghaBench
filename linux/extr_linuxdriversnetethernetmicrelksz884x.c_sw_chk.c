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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 int readw (scalar_t__) ; 

__attribute__((used)) static int sw_chk(struct ksz_hw *hw, u32 addr, u16 bits)
{
	u16 data;

	data = readw(hw->io + addr);
	return (data & bits) == bits;
}