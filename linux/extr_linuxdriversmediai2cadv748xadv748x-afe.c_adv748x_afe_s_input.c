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
struct adv748x_afe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_SDP_INSEL ; 
 struct adv748x_state* adv748x_afe_to_state (struct adv748x_afe*) ; 
 int sdp_write (struct adv748x_state*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adv748x_afe_s_input(struct adv748x_afe *afe, unsigned int input)
{
	struct adv748x_state *state = adv748x_afe_to_state(afe);

	return sdp_write(state, ADV748X_SDP_INSEL, input);
}