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
struct mxl111sf_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXL_GPIO_DIR_OUTPUT ; 
 int mxl111sf_hw_do_set_gpio (struct mxl111sf_state*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mxl111sf_hw_set_gpio(struct mxl111sf_state *state, int gpio, int val)
{
	return mxl111sf_hw_do_set_gpio(state, gpio, MXL_GPIO_DIR_OUTPUT, val);
}