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
typedef  int v4l2_std_id ;
typedef  int /*<<< orphan*/  u32 ;
struct adv748x_state {int dummy; } ;
struct adv748x_afe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_SDP_RO_10 ; 
 int ADV748X_SDP_RO_10_IN_LOCK ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_SIGNAL ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_NTSC_443 ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_PAL_N ; 
 int V4L2_STD_PAL_Nc ; 
 int V4L2_STD_SECAM ; 
 int V4L2_STD_UNKNOWN ; 
 int adv748x_afe_read_ro_map (struct adv748x_state*,int /*<<< orphan*/ ) ; 
 struct adv748x_state* adv748x_afe_to_state (struct adv748x_afe*) ; 

__attribute__((used)) static int adv748x_afe_status(struct adv748x_afe *afe, u32 *signal,
			      v4l2_std_id *std)
{
	struct adv748x_state *state = adv748x_afe_to_state(afe);
	int info;

	/* Read status from reg 0x10 of SDP RO Map */
	info = adv748x_afe_read_ro_map(state, ADV748X_SDP_RO_10);
	if (info < 0)
		return info;

	if (signal)
		*signal = info & ADV748X_SDP_RO_10_IN_LOCK ?
				0 : V4L2_IN_ST_NO_SIGNAL;

	if (!std)
		return 0;

	/* Standard not valid if there is no signal */
	if (!(info & ADV748X_SDP_RO_10_IN_LOCK)) {
		*std = V4L2_STD_UNKNOWN;
		return 0;
	}

	switch (info & 0x70) {
	case 0x00:
		*std = V4L2_STD_NTSC;
		break;
	case 0x10:
		*std = V4L2_STD_NTSC_443;
		break;
	case 0x20:
		*std = V4L2_STD_PAL_M;
		break;
	case 0x30:
		*std = V4L2_STD_PAL_60;
		break;
	case 0x40:
		*std = V4L2_STD_PAL;
		break;
	case 0x50:
		*std = V4L2_STD_SECAM;
		break;
	case 0x60:
		*std = V4L2_STD_PAL_Nc | V4L2_STD_PAL_N;
		break;
	case 0x70:
		*std = V4L2_STD_SECAM;
		break;
	default:
		*std = V4L2_STD_UNKNOWN;
		break;
	}

	return 0;
}