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
typedef  void* u32 ;
struct TYPE_4__ {int /*<<< orphan*/  sliced; int /*<<< orphan*/  vbi; } ;
struct TYPE_5__ {TYPE_1__ fmt; } ;
struct TYPE_6__ {int count; int enc_size; int raw_size; int sliced_size; int fpi; void* enc_start; TYPE_2__ in; } ;
struct ivtv {int hw_flags; scalar_t__ is_60hz; TYPE_3__ vbi; int /*<<< orphan*/  sd_video; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_SET_VBI_CONFIG ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_VBI_LINE ; 
 int CX2341X_MBOX_MAX_DATA ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,void*,void*,int,...) ; 
 int IVTV_HW_CX25840 ; 
 int /*<<< orphan*/  ivtv_api (struct ivtv*,int /*<<< orphan*/ ,int,void**) ; 
 int ivtv_raw_vbi (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_raw_fmt ; 
 int /*<<< orphan*/  s_sliced_fmt ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbi ; 

__attribute__((used)) static void ivtv_vbi_setup(struct ivtv *itv)
{
	int raw = ivtv_raw_vbi(itv);
	u32 data[CX2341X_MBOX_MAX_DATA];
	int lines;
	int i;

	/* Reset VBI */
	ivtv_vapi(itv, CX2341X_ENC_SET_VBI_LINE, 5, 0xffff , 0, 0, 0, 0);

	/* setup VBI registers */
	if (raw)
		v4l2_subdev_call(itv->sd_video, vbi, s_raw_fmt, &itv->vbi.in.fmt.vbi);
	else
		v4l2_subdev_call(itv->sd_video, vbi, s_sliced_fmt, &itv->vbi.in.fmt.sliced);

	/* determine number of lines and total number of VBI bytes.
	   A raw line takes 1443 bytes: 2 * 720 + 4 byte frame header - 1
	   The '- 1' byte is probably an unused U or V byte. Or something...
	   A sliced line takes 51 bytes: 4 byte frame header, 4 byte internal
	   header, 42 data bytes + checksum (to be confirmed) */
	if (raw) {
		lines = itv->vbi.count * 2;
	} else {
		lines = itv->is_60hz ? 24 : 38;
		if (itv->is_60hz && (itv->hw_flags & IVTV_HW_CX25840))
			lines += 2;
	}

	itv->vbi.enc_size = lines * (raw ? itv->vbi.raw_size : itv->vbi.sliced_size);

	/* Note: sliced vs raw flag doesn't seem to have any effect
	   TODO: check mode (0x02) value with older ivtv versions. */
	data[0] = raw | 0x02 | (0xbd << 8);

	/* Every X number of frames a VBI interrupt arrives (frames as in 25 or 30 fps) */
	data[1] = 1;
	/* The VBI frames are stored in a ringbuffer with this size (with a VBI frame as unit) */
	data[2] = raw ? 4 : 4 * (itv->vbi.raw_size / itv->vbi.enc_size);
	/* The start/stop codes determine which VBI lines end up in the raw VBI data area.
	   The codes are from table 24 in the saa7115 datasheet. Each raw/sliced/video line
	   is framed with codes FF0000XX where XX is the SAV/EAV (Start/End of Active Video)
	   code. These values for raw VBI are obtained from a driver disassembly. The sliced
	   start/stop codes was deduced from this, but they do not appear in the driver.
	   Other code pairs that I found are: 0x250E6249/0x13545454 and 0x25256262/0x38137F54.
	   However, I have no idea what these values are for. */
	if (itv->hw_flags & IVTV_HW_CX25840) {
		/* Setup VBI for the cx25840 digitizer */
		if (raw) {
			data[3] = 0x20602060;
			data[4] = 0x30703070;
		} else {
			data[3] = 0xB0F0B0F0;
			data[4] = 0xA0E0A0E0;
		}
		/* Lines per frame */
		data[5] = lines;
		/* bytes per line */
		data[6] = (raw ? itv->vbi.raw_size : itv->vbi.sliced_size);
	} else {
		/* Setup VBI for the saa7115 digitizer */
		if (raw) {
			data[3] = 0x25256262;
			data[4] = 0x387F7F7F;
		} else {
			data[3] = 0xABABECEC;
			data[4] = 0xB6F1F1F1;
		}
		/* Lines per frame */
		data[5] = lines;
		/* bytes per line */
		data[6] = itv->vbi.enc_size / lines;
	}

	IVTV_DEBUG_INFO(
		"Setup VBI API header 0x%08x pkts %d buffs %d ln %d sz %d\n",
			data[0], data[1], data[2], data[5], data[6]);

	ivtv_api(itv, CX2341X_ENC_SET_VBI_CONFIG, 7, data);

	/* returns the VBI encoder memory area. */
	itv->vbi.enc_start = data[2];
	itv->vbi.fpi = data[0];
	if (!itv->vbi.fpi)
		itv->vbi.fpi = 1;

	IVTV_DEBUG_INFO("Setup VBI start 0x%08x frames %d fpi %d\n",
		itv->vbi.enc_start, data[1], itv->vbi.fpi);

	/* select VBI lines.
	   Note that the sliced argument seems to have no effect. */
	for (i = 2; i <= 24; i++) {
		int valid;

		if (itv->is_60hz) {
			valid = i >= 10 && i < 22;
		} else {
			valid = i >= 6 && i < 24;
		}
		ivtv_vapi(itv, CX2341X_ENC_SET_VBI_LINE, 5, i - 1,
				valid, 0 , 0, 0);
		ivtv_vapi(itv, CX2341X_ENC_SET_VBI_LINE, 5, (i - 1) | 0x80000000,
				valid, 0, 0, 0);
	}

	/* Remaining VBI questions:
	   - Is it possible to select particular VBI lines only for inclusion in the MPEG
	   stream? Currently you can only get the first X lines.
	   - Is mixed raw and sliced VBI possible?
	   - What's the meaning of the raw/sliced flag?
	   - What's the meaning of params 2, 3 & 4 of the Select VBI command? */
}