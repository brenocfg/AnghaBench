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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct saa717x_state {int input; int /*<<< orphan*/  tuner_audio_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TUNER_AUDIO_STEREO ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  reg_init_composite_input ; 
 int /*<<< orphan*/  reg_init_svideo_input ; 
 int /*<<< orphan*/  reg_init_tuner_input ; 
 int saa717x_read (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  saa717x_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  saa717x_write_regs (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_audio_mode (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct saa717x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,...) ; 

__attribute__((used)) static int saa717x_s_video_routing(struct v4l2_subdev *sd,
				   u32 input, u32 output, u32 config)
{
	struct saa717x_state *decoder = to_state(sd);
	int is_tuner = input & 0x80;  /* tuner input flag */

	input &= 0x7f;

	v4l2_dbg(1, debug, sd, "decoder set input (%d)\n", input);
	/* inputs from 0-9 are available*/
	/* saa717x have mode0-mode9 but mode5 is reserved. */
	if (input > 9 || input == 5)
		return -EINVAL;

	if (decoder->input != input) {
		int input_line = input;

		decoder->input = input_line;
		v4l2_dbg(1, debug, sd,  "now setting %s input %d\n",
				input_line >= 6 ? "S-Video" : "Composite",
				input_line);

		/* select mode */
		saa717x_write(sd, 0x102,
				(saa717x_read(sd, 0x102) & 0xf0) |
				input_line);

		/* bypass chrominance trap for modes 6..9 */
		saa717x_write(sd, 0x109,
				(saa717x_read(sd, 0x109) & 0x7f) |
				(input_line < 6 ? 0x0 : 0x80));

		/* change audio_mode */
		if (is_tuner) {
			/* tuner */
			set_audio_mode(sd, decoder->tuner_audio_mode);
		} else {
			/* Force to STEREO mode if Composite or
			 * S-Video were chosen */
			set_audio_mode(sd, TUNER_AUDIO_STEREO);
		}
		/* change initialize procedure (Composite/S-Video) */
		if (is_tuner)
			saa717x_write_regs(sd, reg_init_tuner_input);
		else if (input_line >= 6)
			saa717x_write_regs(sd, reg_init_svideo_input);
		else
			saa717x_write_regs(sd, reg_init_composite_input);
	}

	return 0;
}