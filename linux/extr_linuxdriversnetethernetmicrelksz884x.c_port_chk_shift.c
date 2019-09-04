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

__attribute__((used)) static int port_chk_shift(struct ksz_hw *hw, int port, u32 addr, int shift)
{
	u16 data;
	u16 bit = 1 << port;

	data = readw(hw->io + addr);
	data >>= shift;
	return (data & bit) == bit;
}