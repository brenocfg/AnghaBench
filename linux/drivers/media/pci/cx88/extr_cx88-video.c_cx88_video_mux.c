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
struct cx88_core {unsigned int input; int /*<<< orphan*/  tvaudio; scalar_t__ sd_wm8775; } ;
struct TYPE_2__ {int vmux; int gpio0; int gpio1; int gpio2; int gpio3; int type; scalar_t__ audioroute; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_CTL ; 
 int /*<<< orphan*/  AUD_I2SCNTL ; 
 int CX88_VMUX_CABLE ; 
#define  CX88_VMUX_SVIDEO 128 
 int CX88_VMUX_TELEVISION ; 
 int EN_I2SIN_ENABLE ; 
 TYPE_1__ INPUT (unsigned int) ; 
 int /*<<< orphan*/  MO_AFECFG_IO ; 
 int /*<<< orphan*/  MO_FILTER_EVEN ; 
 int /*<<< orphan*/  MO_FILTER_ODD ; 
 int /*<<< orphan*/  MO_GP0_IO ; 
 int /*<<< orphan*/  MO_GP1_IO ; 
 int /*<<< orphan*/  MO_GP2_IO ; 
 int /*<<< orphan*/  MO_GP3_IO ; 
 int /*<<< orphan*/  MO_INPUT_FORMAT ; 
 int /*<<< orphan*/  WW_I2SADC ; 
 int /*<<< orphan*/  audio ; 
 int /*<<< orphan*/  call_all (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx88_set_tvaudio (struct cx88_core*) ; 
 int /*<<< orphan*/  cx_andor (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,unsigned int,int,int,int,int,int) ; 
 int /*<<< orphan*/  s_routing ; 

int cx88_video_mux(struct cx88_core *core, unsigned int input)
{
	/* struct cx88_core *core = dev->core; */

	dprintk(1, "video_mux: %d [vmux=%d,gpio=0x%x,0x%x,0x%x,0x%x]\n",
		input, INPUT(input).vmux,
		INPUT(input).gpio0, INPUT(input).gpio1,
		INPUT(input).gpio2, INPUT(input).gpio3);
	core->input = input;
	cx_andor(MO_INPUT_FORMAT, 0x03 << 14, INPUT(input).vmux << 14);
	cx_write(MO_GP3_IO, INPUT(input).gpio3);
	cx_write(MO_GP0_IO, INPUT(input).gpio0);
	cx_write(MO_GP1_IO, INPUT(input).gpio1);
	cx_write(MO_GP2_IO, INPUT(input).gpio2);

	switch (INPUT(input).type) {
	case CX88_VMUX_SVIDEO:
		cx_set(MO_AFECFG_IO,    0x00000001);
		cx_set(MO_INPUT_FORMAT, 0x00010010);
		cx_set(MO_FILTER_EVEN,  0x00002020);
		cx_set(MO_FILTER_ODD,   0x00002020);
		break;
	default:
		cx_clear(MO_AFECFG_IO,    0x00000001);
		cx_clear(MO_INPUT_FORMAT, 0x00010010);
		cx_clear(MO_FILTER_EVEN,  0x00002020);
		cx_clear(MO_FILTER_ODD,   0x00002020);
		break;
	}

	/*
	 * if there are audioroutes defined, we have an external
	 * ADC to deal with audio
	 */
	if (INPUT(input).audioroute) {
		/*
		 * The wm8775 module has the "2" route hardwired into
		 * the initialization. Some boards may use different
		 * routes for different inputs. HVR-1300 surely does
		 */
		if (core->sd_wm8775) {
			call_all(core, audio, s_routing,
				 INPUT(input).audioroute, 0, 0);
		}
		/*
		 * cx2388's C-ADC is connected to the tuner only.
		 * When used with S-Video, that ADC is busy dealing with
		 * chroma, so an external must be used for baseband audio
		 */
		if (INPUT(input).type != CX88_VMUX_TELEVISION &&
		    INPUT(input).type != CX88_VMUX_CABLE) {
			/* "I2S ADC mode" */
			core->tvaudio = WW_I2SADC;
			cx88_set_tvaudio(core);
		} else {
			/* Normal mode */
			cx_write(AUD_I2SCNTL, 0x0);
			cx_clear(AUD_CTL, EN_I2SIN_ENABLE);
		}
	}

	return 0;
}