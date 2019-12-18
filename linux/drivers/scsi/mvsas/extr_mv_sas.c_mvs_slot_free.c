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
struct mvs_info {int dummy; } ;

/* Variables and functions */
 int RXQ_SLOT_MASK ; 
 int /*<<< orphan*/  mvs_tag_clear (struct mvs_info*,int) ; 

__attribute__((used)) static void mvs_slot_free(struct mvs_info *mvi, u32 rx_desc)
{
	u32 slot_idx = rx_desc & RXQ_SLOT_MASK;
	mvs_tag_clear(mvi, slot_idx);
}