#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cx18_stream {int handle; struct cx18* cx; } ;
struct TYPE_4__ {int /*<<< orphan*/  sliced; int /*<<< orphan*/  vbi; } ;
struct TYPE_5__ {TYPE_1__ fmt; } ;
struct TYPE_6__ {int count; int* start; TYPE_2__ in; } ;
struct cx18 {scalar_t__ is_60hz; TYPE_3__ vbi; int /*<<< orphan*/  sd_av; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_CPU_SET_RAW_VBI_PARAM ; 
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,int,int,int,int,int,int) ; 
 int CX2341X_MBOX_MAX_DATA ; 
 int VBI_ACTIVE_SAMPLES ; 
 int VBI_HBLANK_SAMPLES_50HZ ; 
 int VBI_HBLANK_SAMPLES_60HZ ; 
 int /*<<< orphan*/  cx18_api (struct cx18*,int /*<<< orphan*/ ,int,int*) ; 
 int cx18_raw_vbi (struct cx18*) ; 
 int /*<<< orphan*/  s_raw_fmt ; 
 int /*<<< orphan*/  s_sliced_fmt ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbi ; 

__attribute__((used)) static void cx18_vbi_setup(struct cx18_stream *s)
{
	struct cx18 *cx = s->cx;
	int raw = cx18_raw_vbi(cx);
	u32 data[CX2341X_MBOX_MAX_DATA];
	int lines;

	if (cx->is_60hz) {
		cx->vbi.count = 12;
		cx->vbi.start[0] = 10;
		cx->vbi.start[1] = 273;
	} else {        /* PAL/SECAM */
		cx->vbi.count = 18;
		cx->vbi.start[0] = 6;
		cx->vbi.start[1] = 318;
	}

	/* setup VBI registers */
	if (raw)
		v4l2_subdev_call(cx->sd_av, vbi, s_raw_fmt, &cx->vbi.in.fmt.vbi);
	else
		v4l2_subdev_call(cx->sd_av, vbi, s_sliced_fmt, &cx->vbi.in.fmt.sliced);

	/*
	 * Send the CX18_CPU_SET_RAW_VBI_PARAM API command to setup Encoder Raw
	 * VBI when the first analog capture channel starts, as once it starts
	 * (e.g. MPEG), we can't effect any change in the Encoder Raw VBI setup
	 * (i.e. for the VBI capture channels).  We also send it for each
	 * analog capture channel anyway just to make sure we get the proper
	 * behavior
	 */
	if (raw) {
		lines = cx->vbi.count * 2;
	} else {
		/*
		 * For 525/60 systems, according to the VIP 2 & BT.656 std:
		 * The EAV RP code's Field bit toggles on line 4, a few lines
		 * after the Vertcal Blank bit has already toggled.
		 * Tell the encoder to capture 21-4+1=18 lines per field,
		 * since we want lines 10 through 21.
		 *
		 * For 625/50 systems, according to the VIP 2 & BT.656 std:
		 * The EAV RP code's Field bit toggles on line 1, a few lines
		 * after the Vertcal Blank bit has already toggled.
		 * (We've actually set the digitizer so that the Field bit
		 * toggles on line 2.) Tell the encoder to capture 23-2+1=22
		 * lines per field, since we want lines 6 through 23.
		 */
		lines = cx->is_60hz ? (21 - 4 + 1) * 2 : (23 - 2 + 1) * 2;
	}

	data[0] = s->handle;
	/* Lines per field */
	data[1] = (lines / 2) | ((lines / 2) << 16);
	/* bytes per line */
	data[2] = (raw ? VBI_ACTIVE_SAMPLES
		       : (cx->is_60hz ? VBI_HBLANK_SAMPLES_60HZ
				      : VBI_HBLANK_SAMPLES_50HZ));
	/* Every X number of frames a VBI interrupt arrives
	   (frames as in 25 or 30 fps) */
	data[3] = 1;
	/*
	 * Set the SAV/EAV RP codes to look for as start/stop points
	 * when in VIP-1.1 mode
	 */
	if (raw) {
		/*
		 * Start codes for beginning of "active" line in vertical blank
		 * 0x20 (               VerticalBlank                )
		 * 0x60 (     EvenField VerticalBlank                )
		 */
		data[4] = 0x20602060;
		/*
		 * End codes for end of "active" raw lines and regular lines
		 * 0x30 (               VerticalBlank HorizontalBlank)
		 * 0x70 (     EvenField VerticalBlank HorizontalBlank)
		 * 0x90 (Task                         HorizontalBlank)
		 * 0xd0 (Task EvenField               HorizontalBlank)
		 */
		data[5] = 0x307090d0;
	} else {
		/*
		 * End codes for active video, we want data in the hblank region
		 * 0xb0 (Task         0 VerticalBlank HorizontalBlank)
		 * 0xf0 (Task EvenField VerticalBlank HorizontalBlank)
		 *
		 * Since the V bit is only allowed to toggle in the EAV RP code,
		 * just before the first active region line, these two
		 * are problematic:
		 * 0x90 (Task                         HorizontalBlank)
		 * 0xd0 (Task EvenField               HorizontalBlank)
		 *
		 * We have set the digitzer such that we don't have to worry
		 * about these problem codes.
		 */
		data[4] = 0xB0F0B0F0;
		/*
		 * Start codes for beginning of active line in vertical blank
		 * 0xa0 (Task           VerticalBlank                )
		 * 0xe0 (Task EvenField VerticalBlank                )
		 */
		data[5] = 0xA0E0A0E0;
	}

	CX18_DEBUG_INFO("Setup VBI h: %d lines %x bpl %d fr %d %x %x\n",
			data[0], data[1], data[2], data[3], data[4], data[5]);

	cx18_api(cx, CX18_CPU_SET_RAW_VBI_PARAM, 6, data);
}