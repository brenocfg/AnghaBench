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
 unsigned char ADP5585_COL_SHIFT ; 
 unsigned char ADP5585_MAX_ROW_NUM ; 

__attribute__((used)) static unsigned char adp5585_bit(unsigned char offset)
{
	return (offset > ADP5585_MAX_ROW_NUM) ?
		1u << (offset - ADP5585_COL_SHIFT) : 1u << offset;
}