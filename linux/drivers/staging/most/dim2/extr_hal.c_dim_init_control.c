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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct dim_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAT_CT_VAL_CONTROL ; 
 int /*<<< orphan*/  init_ctrl_async (struct dim_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 dim_init_control(struct dim_channel *ch, u8 is_tx, u16 ch_address,
		    u16 max_buffer_size)
{
	return init_ctrl_async(ch, CAT_CT_VAL_CONTROL, is_tx, ch_address,
			       max_buffer_size);
}