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
typedef  union hdmi_infoframe {int dummy; } hdmi_infoframe ;
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;
struct tda1997x_state {TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  hdmi_infoframe_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,union hdmi_infoframe*) ; 
 int hdmi_infoframe_unpack (union hdmi_infoframe*,int /*<<< orphan*/ *,int) ; 
 int io_readn (struct v4l2_subdev*,int,int,int /*<<< orphan*/ *) ; 
 struct tda1997x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,int) ; 
 int /*<<< orphan*/  v4l_err (TYPE_1__*,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda1997x_log_infoframe(struct v4l2_subdev *sd, int addr)
{
	struct tda1997x_state *state = to_state(sd);
	union hdmi_infoframe frame;
	u8 buffer[40];
	int len, err;

	/* read data */
	len = io_readn(sd, addr, sizeof(buffer), buffer);
	v4l2_dbg(1, debug, sd, "infoframe: addr=%d len=%d\n", addr, len);
	err = hdmi_infoframe_unpack(&frame, buffer, sizeof(buffer));
	if (err) {
		v4l_err(state->client,
			"failed parsing %d byte infoframe: 0x%04x/0x%02x\n",
			len, addr, buffer[0]);
		return err;
	}
	hdmi_infoframe_log(KERN_INFO, &state->client->dev, &frame);

	return 0;
}