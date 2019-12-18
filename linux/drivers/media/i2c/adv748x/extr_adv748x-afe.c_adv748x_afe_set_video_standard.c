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
 int /*<<< orphan*/  ADV748X_SDP_VID_SEL ; 
 int /*<<< orphan*/  ADV748X_SDP_VID_SEL_MASK ; 
 int ADV748X_SDP_VID_SEL_SHIFT ; 
 int /*<<< orphan*/  sdp_clrset (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adv748x_afe_set_video_standard(struct adv748x_state *state,
					  int sdpstd)
{
	sdp_clrset(state, ADV748X_SDP_VID_SEL, ADV748X_SDP_VID_SEL_MASK,
		   (sdpstd & 0xf) << ADV748X_SDP_VID_SEL_SHIFT);
}