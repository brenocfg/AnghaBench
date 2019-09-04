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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ SIZE_4K ; 

__attribute__((used)) static u16 xgene_enet_set_data_len(u32 size)
{
	u16 hw_len;

	hw_len =  (size == SIZE_4K) ? BIT(14) : 0;

	return hw_len;
}