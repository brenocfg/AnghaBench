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
struct adv748x_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_HDMI_LW1 ; 
 int ADV748X_HDMI_LW1_DE_REGEN ; 
 int ADV748X_HDMI_LW1_VERT_FILTER ; 
 int hdmi_read (struct adv748x_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool adv748x_hdmi_has_signal(struct adv748x_state *state)
{
	int val;

	/* Check that VERT_FILTER and DE_REGEN is locked */
	val = hdmi_read(state, ADV748X_HDMI_LW1);
	return (val & ADV748X_HDMI_LW1_VERT_FILTER) &&
	       (val & ADV748X_HDMI_LW1_DE_REGEN);
}