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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int* data; } ;
struct adv7511_state {TYPE_1__ edid; } ;
typedef  int /*<<< orphan*/  hdmi_header ;

/* Variables and functions */
 struct adv7511_state* get_adv7511_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 

__attribute__((used)) static bool edid_verify_header(struct v4l2_subdev *sd, u32 segment)
{
	static const u8 hdmi_header[] = {
		0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
	};
	struct adv7511_state *state = get_adv7511_state(sd);
	u8 *data = state->edid.data;

	if (segment != 0)
		return true;
	return !memcmp(data, hdmi_header, sizeof(hdmi_header));
}