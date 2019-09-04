#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_2__ {int /*<<< orphan*/  ch_ctrl; } ;

/* Variables and functions */
 int VPIF_CH_FID_MASK ; 
 int VPIF_CH_FID_SHIFT ; 
 int regr (int /*<<< orphan*/ ) ; 
 TYPE_1__* vpifregs ; 

int vpif_channel_getfid(u8 channel_id)
{
	return (regr(vpifregs[channel_id].ch_ctrl) & VPIF_CH_FID_MASK)
					>> VPIF_CH_FID_SHIFT;
}