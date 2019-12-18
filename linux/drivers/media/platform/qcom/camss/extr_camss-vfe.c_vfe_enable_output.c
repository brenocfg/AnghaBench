#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct vfe_output {int state; int* wm_idx; int wm_num; int /*<<< orphan*/  reg_update; int /*<<< orphan*/  sof; scalar_t__ wait_reg_update; scalar_t__ wait_sof; scalar_t__ sequence; int /*<<< orphan*/ ** buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  pix_mp; } ;
struct TYPE_7__ {TYPE_1__ fmt; } ;
struct TYPE_8__ {TYPE_2__ active_fmt; } ;
struct TYPE_9__ {int /*<<< orphan*/  entity; } ;
struct vfe_line {int /*<<< orphan*/  id; TYPE_3__ video_out; TYPE_4__ subdev; struct vfe_output output; } ;
struct vfe_hw_ops {int (* get_ub_size ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* reg_update ) (struct vfe_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_camif_cmd ) (struct vfe_device*,int) ;int /*<<< orphan*/  (* set_clamp_cfg ) (struct vfe_device*) ;int /*<<< orphan*/  (* set_crop_cfg ) (struct vfe_device*,struct vfe_line*) ;int /*<<< orphan*/  (* set_scale_cfg ) (struct vfe_device*,struct vfe_line*) ;int /*<<< orphan*/  (* set_demux_cfg ) (struct vfe_device*,struct vfe_line*) ;int /*<<< orphan*/  (* set_xbar_cfg ) (struct vfe_device*,struct vfe_output*,int) ;int /*<<< orphan*/  (* set_realign_cfg ) (struct vfe_device*,struct vfe_line*,int) ;int /*<<< orphan*/  (* set_camif_cfg ) (struct vfe_device*,struct vfe_line*) ;int /*<<< orphan*/  (* set_module_cfg ) (struct vfe_device*,int) ;int /*<<< orphan*/  (* enable_irq_pix_line ) (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* bus_reload_wm ) (struct vfe_device*,int) ;int /*<<< orphan*/  (* wm_enable ) (struct vfe_device*,int,int) ;int /*<<< orphan*/  (* wm_line_based ) (struct vfe_device*,int,int /*<<< orphan*/ *,unsigned int,int) ;int /*<<< orphan*/  (* wm_set_ub_cfg ) (struct vfe_device*,int,int,int) ;int /*<<< orphan*/  (* wm_set_subsample ) (struct vfe_device*,int) ;int /*<<< orphan*/  (* set_cgc_override ) (struct vfe_device*,int,int) ;int /*<<< orphan*/  (* wm_frame_based ) (struct vfe_device*,int,int) ;int /*<<< orphan*/  (* set_rdi_cid ) (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* bus_connect_wm_to_rdi ) (struct vfe_device*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* enable_irq_wm_line ) (struct vfe_device*,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* reg_update_clear ) (struct vfe_device*,int /*<<< orphan*/ ) ;} ;
struct vfe_device {int /*<<< orphan*/  output_lock; TYPE_5__* camss; int /*<<< orphan*/  id; struct vfe_hw_ops* ops; } ;
struct v4l2_subdev {int dummy; } ;
struct media_entity {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int VFE_FRAME_DROP_VAL ; 
 int /*<<< orphan*/  VFE_LINE_PIX ; 
#define  VFE_OUTPUT_CONTINUOUS 129 
 int VFE_OUTPUT_IDLE ; 
 int VFE_OUTPUT_RESERVED ; 
#define  VFE_OUTPUT_SINGLE 128 
 struct media_entity* camss_find_sensor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_skip_frames ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct vfe_device*,int,int) ; 
 int /*<<< orphan*/  stub11 (struct vfe_device*,int) ; 
 int /*<<< orphan*/  stub12 (struct vfe_device*,int,int) ; 
 int /*<<< orphan*/  stub13 (struct vfe_device*,int) ; 
 int /*<<< orphan*/  stub14 (struct vfe_device*,int,int,int) ; 
 int /*<<< orphan*/  stub15 (struct vfe_device*,int,int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  stub16 (struct vfe_device*,int,int) ; 
 int /*<<< orphan*/  stub17 (struct vfe_device*,int) ; 
 int /*<<< orphan*/  stub18 (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub19 (struct vfe_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct vfe_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub20 (struct vfe_device*,struct vfe_line*) ; 
 int /*<<< orphan*/  stub21 (struct vfe_device*,struct vfe_line*,int) ; 
 int /*<<< orphan*/  stub22 (struct vfe_device*,struct vfe_output*,int) ; 
 int /*<<< orphan*/  stub23 (struct vfe_device*,struct vfe_line*) ; 
 int /*<<< orphan*/  stub24 (struct vfe_device*,struct vfe_line*) ; 
 int /*<<< orphan*/  stub25 (struct vfe_device*,struct vfe_line*) ; 
 int /*<<< orphan*/  stub26 (struct vfe_device*) ; 
 int /*<<< orphan*/  stub27 (struct vfe_device*,int) ; 
 int /*<<< orphan*/  stub28 (struct vfe_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct vfe_device*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct vfe_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct vfe_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct vfe_device*,int) ; 
 int /*<<< orphan*/  stub7 (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct vfe_device*,int,int,int) ; 
 int /*<<< orphan*/  stub9 (struct vfe_device*,int,int) ; 
 struct vfe_device* to_vfe (struct vfe_line*) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,struct media_entity*,int /*<<< orphan*/ ,unsigned int*) ; 
 void* vfe_buf_get_pending (struct vfe_output*) ; 
 int /*<<< orphan*/  vfe_output_frame_drop (struct vfe_device*,struct vfe_output*,int) ; 
 int /*<<< orphan*/  vfe_output_init_addrs (struct vfe_device*,struct vfe_output*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfe_enable_output(struct vfe_line *line)
{
	struct vfe_device *vfe = to_vfe(line);
	struct vfe_output *output = &line->output;
	const struct vfe_hw_ops *ops = vfe->ops;
	struct media_entity *sensor;
	unsigned long flags;
	unsigned int frame_skip = 0;
	unsigned int i;
	u16 ub_size;

	ub_size = ops->get_ub_size(vfe->id);
	if (!ub_size)
		return -EINVAL;

	sensor = camss_find_sensor(&line->subdev.entity);
	if (sensor) {
		struct v4l2_subdev *subdev =
					media_entity_to_v4l2_subdev(sensor);

		v4l2_subdev_call(subdev, sensor, g_skip_frames, &frame_skip);
		/* Max frame skip is 29 frames */
		if (frame_skip > VFE_FRAME_DROP_VAL - 1)
			frame_skip = VFE_FRAME_DROP_VAL - 1;
	}

	spin_lock_irqsave(&vfe->output_lock, flags);

	ops->reg_update_clear(vfe, line->id);

	if (output->state != VFE_OUTPUT_RESERVED) {
		dev_err(vfe->camss->dev, "Output is not in reserved state %d\n",
			output->state);
		spin_unlock_irqrestore(&vfe->output_lock, flags);
		return -EINVAL;
	}
	output->state = VFE_OUTPUT_IDLE;

	output->buf[0] = vfe_buf_get_pending(output);
	output->buf[1] = vfe_buf_get_pending(output);

	if (!output->buf[0] && output->buf[1]) {
		output->buf[0] = output->buf[1];
		output->buf[1] = NULL;
	}

	if (output->buf[0])
		output->state = VFE_OUTPUT_SINGLE;

	if (output->buf[1])
		output->state = VFE_OUTPUT_CONTINUOUS;

	switch (output->state) {
	case VFE_OUTPUT_SINGLE:
		vfe_output_frame_drop(vfe, output, 1 << frame_skip);
		break;
	case VFE_OUTPUT_CONTINUOUS:
		vfe_output_frame_drop(vfe, output, 3 << frame_skip);
		break;
	default:
		vfe_output_frame_drop(vfe, output, 0);
		break;
	}

	output->sequence = 0;
	output->wait_sof = 0;
	output->wait_reg_update = 0;
	reinit_completion(&output->sof);
	reinit_completion(&output->reg_update);

	vfe_output_init_addrs(vfe, output, 0);

	if (line->id != VFE_LINE_PIX) {
		ops->set_cgc_override(vfe, output->wm_idx[0], 1);
		ops->enable_irq_wm_line(vfe, output->wm_idx[0], line->id, 1);
		ops->bus_connect_wm_to_rdi(vfe, output->wm_idx[0], line->id);
		ops->wm_set_subsample(vfe, output->wm_idx[0]);
		ops->set_rdi_cid(vfe, line->id, 0);
		ops->wm_set_ub_cfg(vfe, output->wm_idx[0],
				   (ub_size + 1) * output->wm_idx[0], ub_size);
		ops->wm_frame_based(vfe, output->wm_idx[0], 1);
		ops->wm_enable(vfe, output->wm_idx[0], 1);
		ops->bus_reload_wm(vfe, output->wm_idx[0]);
	} else {
		ub_size /= output->wm_num;
		for (i = 0; i < output->wm_num; i++) {
			ops->set_cgc_override(vfe, output->wm_idx[i], 1);
			ops->wm_set_subsample(vfe, output->wm_idx[i]);
			ops->wm_set_ub_cfg(vfe, output->wm_idx[i],
					   (ub_size + 1) * output->wm_idx[i],
					   ub_size);
			ops->wm_line_based(vfe, output->wm_idx[i],
					&line->video_out.active_fmt.fmt.pix_mp,
					i, 1);
			ops->wm_enable(vfe, output->wm_idx[i], 1);
			ops->bus_reload_wm(vfe, output->wm_idx[i]);
		}
		ops->enable_irq_pix_line(vfe, 0, line->id, 1);
		ops->set_module_cfg(vfe, 1);
		ops->set_camif_cfg(vfe, line);
		ops->set_realign_cfg(vfe, line, 1);
		ops->set_xbar_cfg(vfe, output, 1);
		ops->set_demux_cfg(vfe, line);
		ops->set_scale_cfg(vfe, line);
		ops->set_crop_cfg(vfe, line);
		ops->set_clamp_cfg(vfe);
		ops->set_camif_cmd(vfe, 1);
	}

	ops->reg_update(vfe, line->id);

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	return 0;
}