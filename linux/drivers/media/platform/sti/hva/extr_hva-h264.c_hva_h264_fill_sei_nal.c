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
typedef  int u8 ;
typedef  int u32 ;
struct hva_h264_stereo_video_sei {int field_views_flag; int top_field_is_left_view_flag; int current_frame_is_left_view_flag; int next_frame_is_second_view_flag; int left_view_self_contained_flag; int right_view_self_contained_flag; } ;
struct hva_ctx {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  start ;
typedef  int /*<<< orphan*/  info ;
typedef  enum hva_h264_sei_payload_type { ____Placeholder_hva_h264_sei_payload_type } hva_h264_sei_payload_type ;

/* Variables and functions */
 int EINVAL ; 
 int NALU_TYPE_SEI ; 
#define  SEI_BUFFERING_PERIOD 131 
#define  SEI_FRAME_PACKING_ARRANGEMENT 130 
#define  SEI_PICTURE_TIMING 129 
#define  SEI_STEREO_VIDEO_INFO 128 
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (struct hva_h264_stereo_video_sei*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hva_h264_fill_sei_nal(struct hva_ctx *pctx,
				 enum hva_h264_sei_payload_type type,
				 u8 *addr, u32 *size)
{
	struct device *dev = ctx_to_dev(pctx);
	const u8 start[] = { 0x00, 0x00, 0x00, 0x01 };
	struct hva_h264_stereo_video_sei info;
	u8 offset = 7;
	u8 msg = 0;

	/* start code */
	memcpy(addr + *size, start, sizeof(start));
	*size += sizeof(start);

	/* nal_unit_type */
	addr[*size] = NALU_TYPE_SEI;
	*size += 1;

	/* payload type */
	addr[*size] = type;
	*size += 1;

	switch (type) {
	case SEI_STEREO_VIDEO_INFO:
		memset(&info, 0, sizeof(info));

		/* set to top/bottom frame packing arrangement */
		info.field_views_flag = 1;
		info.top_field_is_left_view_flag = 1;

		/* payload size */
		addr[*size] = 1;
		*size += 1;

		/* payload */
		msg = info.field_views_flag << offset--;

		if (info.field_views_flag) {
			msg |= info.top_field_is_left_view_flag <<
			       offset--;
		} else {
			msg |= info.current_frame_is_left_view_flag <<
			       offset--;
			msg |= info.next_frame_is_second_view_flag <<
			       offset--;
		}
		msg |= info.left_view_self_contained_flag << offset--;
		msg |= info.right_view_self_contained_flag << offset--;

		addr[*size] = msg;
		*size += 1;

		addr[*size] = 0x80;
		*size += 1;

		return 0;
	case SEI_BUFFERING_PERIOD:
	case SEI_PICTURE_TIMING:
	case SEI_FRAME_PACKING_ARRANGEMENT:
	default:
		dev_err(dev, "%s   sei nal type not supported %d\n",
			pctx->name, type);
		return -EINVAL;
	}
}