#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {TYPE_1__* iso; } ;
struct s5c73m3 {TYPE_2__ ctrls; } ;
struct TYPE_3__ {scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_ISO ; 
 int V4L2_ISO_SENSITIVITY_MANUAL ; 
 int s5c73m3_isp_command (struct s5c73m3*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s5c73m3_set_iso(struct s5c73m3 *state, int val)
{
	u32 iso;

	if (val == V4L2_ISO_SENSITIVITY_MANUAL)
		iso = state->ctrls.iso->val + 1;
	else
		iso = 0;

	return s5c73m3_isp_command(state, COMM_ISO, iso);
}