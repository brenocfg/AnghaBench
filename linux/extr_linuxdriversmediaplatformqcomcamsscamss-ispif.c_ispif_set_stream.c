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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct ispif_line {int interface; int csid_id; int vfe_id; TYPE_1__* fmt; int /*<<< orphan*/ * pads; struct ispif_device* ispif; } ;
struct ispif_device {int /*<<< orphan*/  config_lock; } ;
typedef  enum ispif_intf { ____Placeholder_ispif_intf } ispif_intf ;
struct TYPE_4__ {scalar_t__ version; } ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 scalar_t__ CAMSS_8x96 ; 
 int /*<<< orphan*/  CMD_DISABLE_FRAME_BOUNDARY ; 
 int /*<<< orphan*/  CMD_ENABLE_FRAME_BOUNDARY ; 
 int ENOLINK ; 
 size_t MSM_ISPIF_PAD_SINK ; 
 int /*<<< orphan*/  ispif_config_irq (struct ispif_device*,int,int,int) ; 
 int /*<<< orphan*/  ispif_config_pack (struct ispif_device*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ispif_select_cid (struct ispif_device*,int,int,int,int) ; 
 int /*<<< orphan*/  ispif_select_clk_mux (struct ispif_device*,int,int,int,int) ; 
 int /*<<< orphan*/  ispif_select_csid (struct ispif_device*,int,int,int,int) ; 
 int /*<<< orphan*/  ispif_set_intf_cmd (struct ispif_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int ispif_validate_intf_status (struct ispif_device*,int,int) ; 
 int ispif_wait_for_stop (struct ispif_device*,int,int) ; 
 int /*<<< orphan*/  media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_camss (struct ispif_device*) ; 
 struct ispif_line* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ispif_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct ispif_line *line = v4l2_get_subdevdata(sd);
	struct ispif_device *ispif = line->ispif;
	enum ispif_intf intf = line->interface;
	u8 csid = line->csid_id;
	u8 vfe = line->vfe_id;
	u8 vc = 0; /* Virtual Channel 0 */
	u8 cid = vc * 4; /* id of Virtual Channel and Data Type set */
	int ret;

	if (enable) {
		if (!media_entity_remote_pad(&line->pads[MSM_ISPIF_PAD_SINK]))
			return -ENOLINK;

		/* Config */

		mutex_lock(&ispif->config_lock);
		ispif_select_clk_mux(ispif, intf, csid, vfe, 1);

		ret = ispif_validate_intf_status(ispif, intf, vfe);
		if (ret < 0) {
			mutex_unlock(&ispif->config_lock);
			return ret;
		}

		ispif_select_csid(ispif, intf, csid, vfe, 1);
		ispif_select_cid(ispif, intf, cid, vfe, 1);
		ispif_config_irq(ispif, intf, vfe, 1);
		if (to_camss(ispif)->version == CAMSS_8x96)
			ispif_config_pack(ispif,
					  line->fmt[MSM_ISPIF_PAD_SINK].code,
					  intf, cid, vfe, 1);
		ispif_set_intf_cmd(ispif, CMD_ENABLE_FRAME_BOUNDARY,
				   intf, vfe, vc);
	} else {
		mutex_lock(&ispif->config_lock);
		ispif_set_intf_cmd(ispif, CMD_DISABLE_FRAME_BOUNDARY,
				   intf, vfe, vc);
		mutex_unlock(&ispif->config_lock);

		ret = ispif_wait_for_stop(ispif, intf, vfe);
		if (ret < 0)
			return ret;

		mutex_lock(&ispif->config_lock);
		if (to_camss(ispif)->version == CAMSS_8x96)
			ispif_config_pack(ispif,
					  line->fmt[MSM_ISPIF_PAD_SINK].code,
					  intf, cid, vfe, 0);
		ispif_config_irq(ispif, intf, vfe, 0);
		ispif_select_cid(ispif, intf, cid, vfe, 0);
		ispif_select_csid(ispif, intf, csid, vfe, 0);
		ispif_select_clk_mux(ispif, intf, csid, vfe, 0);
	}

	mutex_unlock(&ispif->config_lock);

	return 0;
}