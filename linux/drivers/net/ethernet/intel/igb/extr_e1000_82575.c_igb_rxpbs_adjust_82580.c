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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * e1000_82580_rxpbs_table ; 

u16 igb_rxpbs_adjust_82580(u32 data)
{
	u16 ret_val = 0;

	if (data < ARRAY_SIZE(e1000_82580_rxpbs_table))
		ret_val = e1000_82580_rxpbs_table[data];

	return ret_val;
}