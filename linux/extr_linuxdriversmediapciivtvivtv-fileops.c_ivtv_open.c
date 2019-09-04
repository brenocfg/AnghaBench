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
struct video_device {int dummy; } ;
struct ivtv_stream {size_t type; int /*<<< orphan*/  vdev; int /*<<< orphan*/  name; struct ivtv* itv; } ;
struct ivtv_open_id {size_t type; int /*<<< orphan*/  fh; struct ivtv* itv; } ;
struct TYPE_4__ {int v4l2_src_h; scalar_t__ stream_size; } ;
struct ivtv {int hw_flags; int dma_data_req_size; TYPE_2__ yuv_info; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  capturing; TYPE_1__* streams; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IVTV_DEBUG_FILE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*) ; 
 size_t IVTV_DEC_STREAM_TYPE_MPG ; 
 size_t IVTV_DEC_STREAM_TYPE_YUV ; 
 size_t IVTV_ENC_STREAM_TYPE_RAD ; 
 int /*<<< orphan*/  IVTV_ERR (char*,...) ; 
 int /*<<< orphan*/  IVTV_F_I_DEC_YUV ; 
 int /*<<< orphan*/  IVTV_F_I_RADIO_USER ; 
 int /*<<< orphan*/  IVTV_F_S_CLAIMED ; 
 int IVTV_HW_SAA711X ; 
 int /*<<< orphan*/  SAA7115_FREQ_32_11_MHZ ; 
 int /*<<< orphan*/  SAA7115_FREQ_FL_APLL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_audio_set_io (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_call_all (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_call_hw (struct ivtv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ivtv_firmware_check (struct ivtv*,char*) ; 
 scalar_t__ ivtv_init_on_first_open (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_mute (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_udma_alloc (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_unmute (struct ivtv*) ; 
 int /*<<< orphan*/  kfree (struct ivtv_open_id*) ; 
 struct ivtv_open_id* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ read_reg (int) ; 
 int /*<<< orphan*/  s_crystal_freq ; 
 int /*<<< orphan*/  s_radio ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int /*<<< orphan*/  video ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 struct ivtv_stream* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int ivtv_open(struct file *filp)
{
	struct video_device *vdev = video_devdata(filp);
	struct ivtv_stream *s = video_get_drvdata(vdev);
	struct ivtv *itv = s->itv;
	struct ivtv_open_id *item;
	int res = 0;

	IVTV_DEBUG_FILE("open %s\n", s->name);

	if (ivtv_init_on_first_open(itv)) {
		IVTV_ERR("Failed to initialize on device %s\n",
			 video_device_node_name(vdev));
		return -ENXIO;
	}

#ifdef CONFIG_VIDEO_ADV_DEBUG
	/* Unless ivtv_fw_debug is set, error out if firmware dead. */
	if (ivtv_fw_debug) {
		IVTV_WARN("Opening %s with dead firmware lockout disabled\n",
			  video_device_node_name(vdev));
		IVTV_WARN("Selected firmware errors will be ignored\n");
	} else {
#else
	if (1) {
#endif
		res = ivtv_firmware_check(itv, "ivtv_serialized_open");
		if (res == -EAGAIN)
			res = ivtv_firmware_check(itv, "ivtv_serialized_open");
		if (res < 0)
			return -EIO;
	}

	if (s->type == IVTV_DEC_STREAM_TYPE_MPG &&
		test_bit(IVTV_F_S_CLAIMED, &itv->streams[IVTV_DEC_STREAM_TYPE_YUV].s_flags))
		return -EBUSY;

	if (s->type == IVTV_DEC_STREAM_TYPE_YUV &&
		test_bit(IVTV_F_S_CLAIMED, &itv->streams[IVTV_DEC_STREAM_TYPE_MPG].s_flags))
		return -EBUSY;

	if (s->type == IVTV_DEC_STREAM_TYPE_YUV) {
		if (read_reg(0x82c) == 0) {
			IVTV_ERR("Tried to open YUV output device but need to send data to mpeg decoder before it can be used\n");
			/* return -ENODEV; */
		}
		ivtv_udma_alloc(itv);
	}

	/* Allocate memory */
	item = kzalloc(sizeof(struct ivtv_open_id), GFP_KERNEL);
	if (NULL == item) {
		IVTV_DEBUG_WARN("nomem on v4l2 open\n");
		return -ENOMEM;
	}
	v4l2_fh_init(&item->fh, &s->vdev);
	item->itv = itv;
	item->type = s->type;

	filp->private_data = &item->fh;
	v4l2_fh_add(&item->fh);

	if (item->type == IVTV_ENC_STREAM_TYPE_RAD &&
			v4l2_fh_is_singular_file(filp)) {
		if (!test_bit(IVTV_F_I_RADIO_USER, &itv->i_flags)) {
			if (atomic_read(&itv->capturing) > 0) {
				/* switching to radio while capture is
				   in progress is not polite */
				v4l2_fh_del(&item->fh);
				v4l2_fh_exit(&item->fh);
				kfree(item);
				return -EBUSY;
			}
		}
		/* Mark that the radio is being used. */
		set_bit(IVTV_F_I_RADIO_USER, &itv->i_flags);
		/* We have the radio */
		ivtv_mute(itv);
		/* Switch tuner to radio */
		ivtv_call_all(itv, tuner, s_radio);
		/* Select the correct audio input (i.e. radio tuner) */
		ivtv_audio_set_io(itv);
		if (itv->hw_flags & IVTV_HW_SAA711X) {
			ivtv_call_hw(itv, IVTV_HW_SAA711X, video, s_crystal_freq,
				SAA7115_FREQ_32_11_MHZ, SAA7115_FREQ_FL_APLL);
		}
		/* Done! Unmute and continue. */
		ivtv_unmute(itv);
	}

	/* YUV or MPG Decoding Mode? */
	if (s->type == IVTV_DEC_STREAM_TYPE_MPG) {
		clear_bit(IVTV_F_I_DEC_YUV, &itv->i_flags);
	} else if (s->type == IVTV_DEC_STREAM_TYPE_YUV) {
		set_bit(IVTV_F_I_DEC_YUV, &itv->i_flags);
		/* For yuv, we need to know the dma size before we start */
		itv->dma_data_req_size =
				1080 * ((itv->yuv_info.v4l2_src_h + 31) & ~31);
		itv->yuv_info.stream_size = 0;
	}
	return 0;
}