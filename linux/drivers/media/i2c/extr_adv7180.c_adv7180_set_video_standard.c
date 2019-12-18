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
struct adv7180_state {TYPE_1__* chip_info; } ;
struct TYPE_2__ {int (* set_std ) (struct adv7180_state*,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (struct adv7180_state*,unsigned int) ; 

__attribute__((used)) static int adv7180_set_video_standard(struct adv7180_state *state,
	unsigned int std)
{
	return state->chip_info->set_std(state, std);
}