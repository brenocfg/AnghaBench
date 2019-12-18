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
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ audioroute; int /*<<< orphan*/  gpio2; int /*<<< orphan*/  gpio1; int /*<<< orphan*/  gpio0; int /*<<< orphan*/  gpio3; } ;
struct TYPE_4__ {TYPE_1__ radio; } ;
struct cx88_core {int /*<<< orphan*/  tvaudio; TYPE_2__ board; scalar_t__ sd_wm8775; } ;
struct cx8800_dev {struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_GP0_IO ; 
 int /*<<< orphan*/  MO_GP1_IO ; 
 int /*<<< orphan*/  MO_GP2_IO ; 
 int /*<<< orphan*/  MO_GP3_IO ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  WW_FM ; 
 int /*<<< orphan*/  WW_I2SADC ; 
 int /*<<< orphan*/  audio ; 
 int /*<<< orphan*/  call_all (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  cx88_set_stereo (struct cx88_core*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx88_set_tvaudio (struct cx88_core*) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_radio ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_fh_open (struct file*) ; 
 struct cx8800_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int radio_open(struct file *file)
{
	struct cx8800_dev *dev = video_drvdata(file);
	struct cx88_core *core = dev->core;
	int ret = v4l2_fh_open(file);

	if (ret)
		return ret;

	cx_write(MO_GP3_IO, core->board.radio.gpio3);
	cx_write(MO_GP0_IO, core->board.radio.gpio0);
	cx_write(MO_GP1_IO, core->board.radio.gpio1);
	cx_write(MO_GP2_IO, core->board.radio.gpio2);
	if (core->board.radio.audioroute) {
		if (core->sd_wm8775) {
			call_all(core, audio, s_routing,
				 core->board.radio.audioroute, 0, 0);
		}
		/* "I2S ADC mode" */
		core->tvaudio = WW_I2SADC;
		cx88_set_tvaudio(core);
	} else {
		/* FM Mode */
		core->tvaudio = WW_FM;
		cx88_set_tvaudio(core);
		cx88_set_stereo(core, V4L2_TUNER_MODE_STEREO, 1);
	}
	call_all(core, tuner, s_radio);
	return 0;
}