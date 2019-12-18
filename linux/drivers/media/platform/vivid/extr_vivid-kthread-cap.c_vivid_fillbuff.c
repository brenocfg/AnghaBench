#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_74__   TYPE_9__ ;
typedef  struct TYPE_73__   TYPE_8__ ;
typedef  struct TYPE_72__   TYPE_7__ ;
typedef  struct TYPE_71__   TYPE_6__ ;
typedef  struct TYPE_70__   TYPE_5__ ;
typedef  struct TYPE_69__   TYPE_4__ ;
typedef  struct TYPE_68__   TYPE_3__ ;
typedef  struct TYPE_67__   TYPE_37__ ;
typedef  struct TYPE_66__   TYPE_36__ ;
typedef  struct TYPE_65__   TYPE_35__ ;
typedef  struct TYPE_64__   TYPE_34__ ;
typedef  struct TYPE_63__   TYPE_33__ ;
typedef  struct TYPE_62__   TYPE_32__ ;
typedef  struct TYPE_61__   TYPE_31__ ;
typedef  struct TYPE_60__   TYPE_30__ ;
typedef  struct TYPE_59__   TYPE_2__ ;
typedef  struct TYPE_58__   TYPE_29__ ;
typedef  struct TYPE_57__   TYPE_28__ ;
typedef  struct TYPE_56__   TYPE_27__ ;
typedef  struct TYPE_55__   TYPE_26__ ;
typedef  struct TYPE_54__   TYPE_25__ ;
typedef  struct TYPE_53__   TYPE_24__ ;
typedef  struct TYPE_52__   TYPE_23__ ;
typedef  struct TYPE_51__   TYPE_22__ ;
typedef  struct TYPE_50__   TYPE_21__ ;
typedef  struct TYPE_49__   TYPE_20__ ;
typedef  struct TYPE_48__   TYPE_1__ ;
typedef  struct TYPE_47__   TYPE_19__ ;
typedef  struct TYPE_46__   TYPE_18__ ;
typedef  struct TYPE_45__   TYPE_17__ ;
typedef  struct TYPE_44__   TYPE_16__ ;
typedef  struct TYPE_43__   TYPE_15__ ;
typedef  struct TYPE_42__   TYPE_14__ ;
typedef  struct TYPE_41__   TYPE_13__ ;
typedef  struct TYPE_40__   TYPE_12__ ;
typedef  struct TYPE_39__   TYPE_11__ ;
typedef  struct TYPE_38__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_67__ {int /*<<< orphan*/  lock; } ;
struct TYPE_51__ {int /*<<< orphan*/  lock; } ;
struct TYPE_45__ {int /*<<< orphan*/  lock; } ;
struct TYPE_69__ {int width; int height; } ;
struct tpg_data {int /*<<< orphan*/  buf_height; int /*<<< orphan*/  bytesperline; } ;
struct vivid_dev {scalar_t__ field_cap; int* std_cap; size_t input; int vid_cap_seq_count; int* must_blank; unsigned int ms_vid_cap; int osd_mode; char* osd; scalar_t__ osd_jiffies; scalar_t__ button_pressed; TYPE_37__ ctrl_hdl_user_gen; TYPE_36__* int_menu; TYPE_34__* string; TYPE_32__* menu; TYPE_30__* boolean; TYPE_28__* int32; TYPE_26__* bitmask; TYPE_24__* int64; TYPE_22__ ctrl_hdl_user_aud; TYPE_21__* mute; TYPE_19__* volume; TYPE_17__ ctrl_hdl_user_vid; TYPE_16__* alpha; TYPE_14__* autogain; TYPE_12__* hue; TYPE_10__* saturation; TYPE_8__* contrast; TYPE_6__* brightness; int /*<<< orphan*/  gain; TYPE_4__ src_rect; scalar_t__ jiffies_vid_cap; TYPE_1__* fmt_cap; int /*<<< orphan*/ * dv_timings_signal_mode; int /*<<< orphan*/ * std_signal_mode; scalar_t__ can_loop_video; scalar_t__ loop_video; struct tpg_data tpg; } ;
struct TYPE_59__ {size_t index; } ;
struct TYPE_68__ {int sequence; scalar_t__ field; TYPE_2__ vb2_buf; } ;
struct vivid_buffer {TYPE_3__ vb; } ;
typedef  int /*<<< orphan*/  str ;
typedef  int s32 ;
struct TYPE_74__ {int val; } ;
struct TYPE_72__ {int val; } ;
struct TYPE_73__ {TYPE_7__ cur; } ;
struct TYPE_70__ {int val; } ;
struct TYPE_71__ {TYPE_5__ cur; } ;
struct TYPE_65__ {size_t val; } ;
struct TYPE_66__ {TYPE_35__ cur; int /*<<< orphan*/ * qmenu_int; } ;
struct TYPE_63__ {char* p_char; } ;
struct TYPE_64__ {TYPE_33__ p_cur; } ;
struct TYPE_61__ {size_t val; } ;
struct TYPE_62__ {char** qmenu; TYPE_31__ cur; } ;
struct TYPE_58__ {int val; } ;
struct TYPE_60__ {TYPE_29__ cur; } ;
struct TYPE_56__ {int val; } ;
struct TYPE_57__ {TYPE_27__ cur; } ;
struct TYPE_54__ {int /*<<< orphan*/  val; } ;
struct TYPE_55__ {TYPE_25__ cur; } ;
struct TYPE_52__ {int /*<<< orphan*/ * p_s64; } ;
struct TYPE_53__ {TYPE_23__ p_cur; } ;
struct TYPE_49__ {int val; } ;
struct TYPE_50__ {TYPE_20__ cur; } ;
struct TYPE_48__ {int* data_offset; } ;
struct TYPE_46__ {int val; } ;
struct TYPE_47__ {TYPE_18__ cur; } ;
struct TYPE_43__ {int val; } ;
struct TYPE_44__ {TYPE_15__ cur; } ;
struct TYPE_41__ {int val; } ;
struct TYPE_42__ {TYPE_13__ cur; } ;
struct TYPE_39__ {int val; } ;
struct TYPE_40__ {TYPE_11__ cur; } ;
struct TYPE_38__ {TYPE_9__ cur; } ;

/* Variables and functions */
 int HZ ; 
 int TPG_MAX_PLANES ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 scalar_t__ V4L2_FIELD_BOTTOM ; 
 scalar_t__ V4L2_FIELD_HAS_T_OR_B (scalar_t__) ; 
 scalar_t__ V4L2_FIELD_TOP ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  VIVID_INVALID_SIGNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 unsigned int jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 void* plane_vaddr (struct tpg_data*,struct vivid_buffer*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  tpg_calc_text_basep (struct tpg_data*,int /*<<< orphan*/ ***,unsigned int,void*) ; 
 int /*<<< orphan*/  tpg_fill_plane_buffer (struct tpg_data*,int /*<<< orphan*/ ,unsigned int,void*) ; 
 unsigned int tpg_g_buffers (struct tpg_data*) ; 
 unsigned int tpg_g_planes (struct tpg_data*) ; 
 int /*<<< orphan*/  tpg_gen_text (struct tpg_data*,int /*<<< orphan*/ ***,unsigned int,int,char*) ; 
 int /*<<< orphan*/  tpg_s_field (struct tpg_data*,scalar_t__,int) ; 
 int /*<<< orphan*/  tpg_s_perc_fill_blank (struct tpg_data*,int) ; 
 int v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 scalar_t__ vivid_copy_buffer (struct vivid_dev*,unsigned int,void*,struct vivid_buffer*) ; 
 int /*<<< orphan*/  vivid_get_std_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_hdmi_cap (struct vivid_dev*) ; 
 int vivid_is_sdtv_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_svid_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_precalc_copy_rects (struct vivid_dev*) ; 

__attribute__((used)) static void vivid_fillbuff(struct vivid_dev *dev, struct vivid_buffer *buf)
{
	struct tpg_data *tpg = &dev->tpg;
	unsigned factor = V4L2_FIELD_HAS_T_OR_B(dev->field_cap) ? 2 : 1;
	unsigned line_height = 16 / factor;
	bool is_tv = vivid_is_sdtv_cap(dev);
	bool is_60hz = is_tv && (dev->std_cap[dev->input] & V4L2_STD_525_60);
	unsigned p;
	int line = 1;
	u8 *basep[TPG_MAX_PLANES][2];
	unsigned ms;
	char str[100];
	s32 gain;
	bool is_loop = false;

	if (dev->loop_video && dev->can_loop_video &&
		((vivid_is_svid_cap(dev) &&
		!VIVID_INVALID_SIGNAL(dev->std_signal_mode[dev->input])) ||
		(vivid_is_hdmi_cap(dev) &&
		!VIVID_INVALID_SIGNAL(dev->dv_timings_signal_mode[dev->input]))))
		is_loop = true;

	buf->vb.sequence = dev->vid_cap_seq_count;
	if (dev->field_cap == V4L2_FIELD_ALTERNATE) {
		/*
		 * 60 Hz standards start with the bottom field, 50 Hz standards
		 * with the top field. So if the 0-based seq_count is even,
		 * then the field is TOP for 50 Hz and BOTTOM for 60 Hz
		 * standards.
		 */
		buf->vb.field = ((dev->vid_cap_seq_count & 1) ^ is_60hz) ?
			V4L2_FIELD_BOTTOM : V4L2_FIELD_TOP;
		/*
		 * The sequence counter counts frames, not fields. So divide
		 * by two.
		 */
		buf->vb.sequence /= 2;
	} else {
		buf->vb.field = dev->field_cap;
	}
	tpg_s_field(tpg, buf->vb.field,
		    dev->field_cap == V4L2_FIELD_ALTERNATE);
	tpg_s_perc_fill_blank(tpg, dev->must_blank[buf->vb.vb2_buf.index]);

	vivid_precalc_copy_rects(dev);

	for (p = 0; p < tpg_g_planes(tpg); p++) {
		void *vbuf = plane_vaddr(tpg, buf, p,
					 tpg->bytesperline, tpg->buf_height);

		/*
		 * The first plane of a multiplanar format has a non-zero
		 * data_offset. This helps testing whether the application
		 * correctly supports non-zero data offsets.
		 */
		if (p < tpg_g_buffers(tpg) && dev->fmt_cap->data_offset[p]) {
			memset(vbuf, dev->fmt_cap->data_offset[p] & 0xff,
			       dev->fmt_cap->data_offset[p]);
			vbuf += dev->fmt_cap->data_offset[p];
		}
		tpg_calc_text_basep(tpg, basep, p, vbuf);
		if (!is_loop || vivid_copy_buffer(dev, p, vbuf, buf))
			tpg_fill_plane_buffer(tpg, vivid_get_std_cap(dev),
					p, vbuf);
	}
	dev->must_blank[buf->vb.vb2_buf.index] = false;

	/* Updates stream time, only update at the start of a new frame. */
	if (dev->field_cap != V4L2_FIELD_ALTERNATE ||
			(dev->vid_cap_seq_count & 1) == 0)
		dev->ms_vid_cap =
			jiffies_to_msecs(jiffies - dev->jiffies_vid_cap);

	ms = dev->ms_vid_cap;
	if (dev->osd_mode <= 1) {
		snprintf(str, sizeof(str), " %02d:%02d:%02d:%03d %u%s",
				(ms / (60 * 60 * 1000)) % 24,
				(ms / (60 * 1000)) % 60,
				(ms / 1000) % 60,
				ms % 1000,
				buf->vb.sequence,
				(dev->field_cap == V4L2_FIELD_ALTERNATE) ?
					(buf->vb.field == V4L2_FIELD_TOP ?
					 " top" : " bottom") : "");
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
	}
	if (dev->osd_mode == 0) {
		snprintf(str, sizeof(str), " %dx%d, input %d ",
				dev->src_rect.width, dev->src_rect.height, dev->input);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);

		gain = v4l2_ctrl_g_ctrl(dev->gain);
		mutex_lock(dev->ctrl_hdl_user_vid.lock);
		snprintf(str, sizeof(str),
			" brightness %3d, contrast %3d, saturation %3d, hue %d ",
			dev->brightness->cur.val,
			dev->contrast->cur.val,
			dev->saturation->cur.val,
			dev->hue->cur.val);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		snprintf(str, sizeof(str),
			" autogain %d, gain %3d, alpha 0x%02x ",
			dev->autogain->cur.val, gain, dev->alpha->cur.val);
		mutex_unlock(dev->ctrl_hdl_user_vid.lock);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		mutex_lock(dev->ctrl_hdl_user_aud.lock);
		snprintf(str, sizeof(str),
			" volume %3d, mute %d ",
			dev->volume->cur.val, dev->mute->cur.val);
		mutex_unlock(dev->ctrl_hdl_user_aud.lock);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		mutex_lock(dev->ctrl_hdl_user_gen.lock);
		snprintf(str, sizeof(str), " int32 %d, int64 %lld, bitmask %08x ",
			dev->int32->cur.val,
			*dev->int64->p_cur.p_s64,
			dev->bitmask->cur.val);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		snprintf(str, sizeof(str), " boolean %d, menu %s, string \"%s\" ",
			dev->boolean->cur.val,
			dev->menu->qmenu[dev->menu->cur.val],
			dev->string->p_cur.p_char);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		snprintf(str, sizeof(str), " integer_menu %lld, value %d ",
			dev->int_menu->qmenu_int[dev->int_menu->cur.val],
			dev->int_menu->cur.val);
		mutex_unlock(dev->ctrl_hdl_user_gen.lock);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		if (dev->button_pressed) {
			dev->button_pressed--;
			snprintf(str, sizeof(str), " button pressed!");
			tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		}
		if (dev->osd[0]) {
			if (vivid_is_hdmi_cap(dev)) {
				snprintf(str, sizeof(str),
					 " OSD \"%s\"", dev->osd);
				tpg_gen_text(tpg, basep, line++ * line_height,
					     16, str);
			}
			if (dev->osd_jiffies &&
			    time_is_before_jiffies(dev->osd_jiffies + 5 * HZ)) {
				dev->osd[0] = 0;
				dev->osd_jiffies = 0;
			}
		}
	}
}