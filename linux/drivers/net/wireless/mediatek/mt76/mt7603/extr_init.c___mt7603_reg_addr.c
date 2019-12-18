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
typedef  int u32 ;
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int mt7603_reg_map (struct mt7603_dev*,int) ; 

__attribute__((used)) static u32 __mt7603_reg_addr(struct mt7603_dev *dev, u32 addr)
{
	if (addr < 0x100000)
		return addr;

	return mt7603_reg_map(dev, addr);
}