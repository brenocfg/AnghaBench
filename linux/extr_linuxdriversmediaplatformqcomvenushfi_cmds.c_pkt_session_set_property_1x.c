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
typedef  int u32 ;
struct hfi_vpe_color_space_conversion {int /*<<< orphan*/  csc_limit; int /*<<< orphan*/  csc_bias; int /*<<< orphan*/  csc_matrix; } ;
struct hfi_vc1e_perf_cfg_type {int /*<<< orphan*/  search_range_y_subsampled; int /*<<< orphan*/  search_range_x_subsampled; } ;
struct hfi_uncompressed_format_select {int /*<<< orphan*/  format; int /*<<< orphan*/  buffer_type; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct TYPE_4__ {TYPE_1__ hdr; int /*<<< orphan*/  session_id; } ;
struct hfi_session_set_property_pkt {int* data; int num_properties; TYPE_2__ shdr; } ;
struct hfi_scs_threshold {int threshold_value; } ;
struct hfi_quantization_range {int min_qp; int max_qp; int /*<<< orphan*/  layer_id; } ;
struct hfi_quantization {int /*<<< orphan*/  layer_id; int /*<<< orphan*/  qp_b; int /*<<< orphan*/  qp_p; int /*<<< orphan*/  qp_i; } ;
struct hfi_profile_level {int level; int /*<<< orphan*/  profile; } ;
struct hfi_operations_type {int /*<<< orphan*/  flip; int /*<<< orphan*/  rotation; } ;
struct hfi_nal_stream_format_select {int /*<<< orphan*/  format; } ;
struct hfi_mvc_buffer_layout_descp_type {int /*<<< orphan*/  ngap; int /*<<< orphan*/  bright_view_first; int /*<<< orphan*/  layout_type; } ;
struct hfi_multi_stream {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  enable; int /*<<< orphan*/  buffer_type; } ;
struct hfi_multi_slice_control {int /*<<< orphan*/  slice_size; int /*<<< orphan*/  multi_slice; } ;
struct hfi_mpeg4_time_resolution {int /*<<< orphan*/  time_increment_resolution; } ;
struct hfi_mpeg4_header_extension {int /*<<< orphan*/  header_extension; } ;
struct hfi_max_num_b_frames {int max_num_b_frames; } ;
struct hfi_ltr_use {int /*<<< orphan*/  use_constrnt; int /*<<< orphan*/  ref_ltr; int /*<<< orphan*/  frames; } ;
struct hfi_ltr_mode {int /*<<< orphan*/  trust_mode; int /*<<< orphan*/  ltr_count; int /*<<< orphan*/  ltr_mode; } ;
struct hfi_ltr_mark {int /*<<< orphan*/  mark_frame; } ;
struct hfi_intra_refresh {int /*<<< orphan*/  cir_mbs; int /*<<< orphan*/  air_ref; int /*<<< orphan*/  air_mbs; int /*<<< orphan*/  mode; } ;
struct hfi_intra_period {int /*<<< orphan*/  bframes; int /*<<< orphan*/  pframes; } ;
struct hfi_initial_quantization {int /*<<< orphan*/  qp_b; int /*<<< orphan*/  qp_p; int /*<<< orphan*/  qp_i; int /*<<< orphan*/  init_qp_enable; } ;
struct hfi_idr_period {int /*<<< orphan*/  idr_period; } ;
struct hfi_hybrid_hierp {int /*<<< orphan*/  layers; } ;
struct hfi_h264_vui_timing_info {int /*<<< orphan*/  time_scale; int /*<<< orphan*/  fixed_framerate; int /*<<< orphan*/  enable; } ;
struct hfi_h264_entropy_control {int /*<<< orphan*/  cabac_model; int /*<<< orphan*/  entropy_mode; } ;
struct hfi_h264_db_control {int /*<<< orphan*/  slice_beta_offset; int /*<<< orphan*/  slice_alpha_offset; int /*<<< orphan*/  mode; } ;
struct hfi_framesize {int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  buffer_type; } ;
struct hfi_framerate {int /*<<< orphan*/  framerate; int /*<<< orphan*/  buffer_type; } ;
struct hfi_enable_picture {int /*<<< orphan*/  picture_type; } ;
struct hfi_enable {int /*<<< orphan*/  enable; } ;
struct hfi_display_picture_buffer_count {int /*<<< orphan*/  enable; int /*<<< orphan*/  count; } ;
struct hfi_conceal_color {int conceal_color; } ;
struct hfi_buffer_size_actual {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct hfi_buffer_display_hold_count_actual {int /*<<< orphan*/  type; int /*<<< orphan*/  hold_count; } ;
struct hfi_buffer_count_actual {int /*<<< orphan*/  type; int /*<<< orphan*/  count_actual; } ;
struct hfi_buffer_alloc_mode {int /*<<< orphan*/  mode; int /*<<< orphan*/  type; } ;
struct hfi_bitrate {int /*<<< orphan*/  layer_id; int /*<<< orphan*/  bitrate; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  HFI_CMD_SESSION_SET_PROPERTY ; 
#define  HFI_DIVX_FORMAT_4 244 
#define  HFI_DIVX_FORMAT_5 243 
#define  HFI_DIVX_FORMAT_6 242 
#define  HFI_FLIP_HORIZONTAL 241 
#define  HFI_FLIP_NONE 240 
#define  HFI_FLIP_VERTICAL 239 
#define  HFI_H264_DB_MODE_ALL_BOUNDARY 238 
#define  HFI_H264_DB_MODE_DISABLE 237 
#define  HFI_H264_DB_MODE_SKIP_SLICE_BOUNDARY 236 
 int /*<<< orphan*/  HFI_H264_ENTROPY_CABAC ; 
 int /*<<< orphan*/  HFI_H264_PROFILE_HIGH ; 
#define  HFI_INTRA_REFRESH_ADAPTIVE 235 
#define  HFI_INTRA_REFRESH_CYCLIC 234 
#define  HFI_INTRA_REFRESH_CYCLIC_ADAPTIVE 233 
#define  HFI_INTRA_REFRESH_NONE 232 
#define  HFI_INTRA_REFRESH_RANDOM 231 
#define  HFI_LTR_MODE_DISABLE 230 
#define  HFI_LTR_MODE_MANUAL 229 
#define  HFI_LTR_MODE_PERIODIC 228 
#define  HFI_MULTI_SLICE_BY_BYTE_COUNT 227 
#define  HFI_MULTI_SLICE_BY_MB_COUNT 226 
#define  HFI_MULTI_SLICE_GOB 225 
#define  HFI_MULTI_SLICE_OFF 224 
#define  HFI_MVC_BUFFER_LAYOUT_SEQ 223 
#define  HFI_MVC_BUFFER_LAYOUT_TOP_BOTTOM 222 
#define  HFI_OUTPUT_ORDER_DECODE 221 
#define  HFI_OUTPUT_ORDER_DISPLAY 220 
#define  HFI_PROPERTY_CONFIG_BATCH_INFO 219 
#define  HFI_PROPERTY_CONFIG_BUFFER_REQUIREMENTS 218 
#define  HFI_PROPERTY_CONFIG_FRAME_RATE 217 
#define  HFI_PROPERTY_CONFIG_PRIORITY 216 
#define  HFI_PROPERTY_CONFIG_REALTIME 215 
#define  HFI_PROPERTY_CONFIG_VDEC_MB_ERROR_MAP_REPORTING 214 
#define  HFI_PROPERTY_CONFIG_VDEC_POST_LOOP_DEBLOCKER 213 
#define  HFI_PROPERTY_CONFIG_VENC_HIER_P_ENH_LAYER 212 
#define  HFI_PROPERTY_CONFIG_VENC_IDR_PERIOD 211 
#define  HFI_PROPERTY_CONFIG_VENC_INTRA_PERIOD 210 
#define  HFI_PROPERTY_CONFIG_VENC_MARKLTRFRAME 209 
#define  HFI_PROPERTY_CONFIG_VENC_MAX_BITRATE 208 
#define  HFI_PROPERTY_CONFIG_VENC_PERF_MODE 207 
#define  HFI_PROPERTY_CONFIG_VENC_REQUEST_SYNC_FRAME 206 
#define  HFI_PROPERTY_CONFIG_VENC_SYNC_FRAME_SEQUENCE_HEADER 205 
#define  HFI_PROPERTY_CONFIG_VENC_TARGET_BITRATE 204 
#define  HFI_PROPERTY_CONFIG_VENC_USELTRFRAME 203 
#define  HFI_PROPERTY_CONFIG_VPE_DEINTERLACE 202 
#define  HFI_PROPERTY_CONFIG_VPE_OPERATIONS 201 
#define  HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE 200 
#define  HFI_PROPERTY_PARAM_BUFFER_COUNT_ACTUAL 199 
#define  HFI_PROPERTY_PARAM_BUFFER_DISPLAY_HOLD_COUNT_ACTUAL 198 
#define  HFI_PROPERTY_PARAM_BUFFER_SIZE_ACTUAL 197 
#define  HFI_PROPERTY_PARAM_CAPABILITY_SUPPORTED 196 
#define  HFI_PROPERTY_PARAM_CHROMA_SITE 195 
#define  HFI_PROPERTY_PARAM_CODEC_SUPPORTED 194 
#define  HFI_PROPERTY_PARAM_DIVX_FORMAT 193 
#define  HFI_PROPERTY_PARAM_FRAME_SIZE 192 
#define  HFI_PROPERTY_PARAM_INTERLACE_FORMAT_SUPPORTED 191 
#define  HFI_PROPERTY_PARAM_MAX_SEQUENCE_HEADER_SIZE 190 
#define  HFI_PROPERTY_PARAM_MULTI_VIEW_FORMAT 189 
#define  HFI_PROPERTY_PARAM_MVC_BUFFER_LAYOUT 188 
#define  HFI_PROPERTY_PARAM_NAL_STREAM_FORMAT_SELECT 187 
#define  HFI_PROPERTY_PARAM_NAL_STREAM_FORMAT_SUPPORTED 186 
#define  HFI_PROPERTY_PARAM_PROFILE_LEVEL_CURRENT 185 
#define  HFI_PROPERTY_PARAM_PROFILE_LEVEL_SUPPORTED 184 
#define  HFI_PROPERTY_PARAM_PROPERTIES_SUPPORTED 183 
#define  HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SELECT 182 
#define  HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SUPPORTED 181 
#define  HFI_PROPERTY_PARAM_VDEC_CONCEAL_COLOR 180 
#define  HFI_PROPERTY_PARAM_VDEC_CONTINUE_DATA_TRANSFER 179 
#define  HFI_PROPERTY_PARAM_VDEC_DISPLAY_PICTURE_BUFFER_COUNT 178 
#define  HFI_PROPERTY_PARAM_VDEC_FRAME_ASSEMBLY 177 
#define  HFI_PROPERTY_PARAM_VDEC_H264_ENTROPY_SWITCHING 176 
#define  HFI_PROPERTY_PARAM_VDEC_MB_QUANTIZATION 175 
#define  HFI_PROPERTY_PARAM_VDEC_MULTI_STREAM 174 
#define  HFI_PROPERTY_PARAM_VDEC_MULTI_VIEW_SELECT 173 
#define  HFI_PROPERTY_PARAM_VDEC_NONCP_OUTPUT2 172 
#define  HFI_PROPERTY_PARAM_VDEC_NUM_CONCEALED_MB 171 
#define  HFI_PROPERTY_PARAM_VDEC_OUTPUT2_KEEP_ASPECT_RATIO 170 
#define  HFI_PROPERTY_PARAM_VDEC_OUTPUT_ORDER 169 
#define  HFI_PROPERTY_PARAM_VDEC_PICTURE_TYPE_DECODE 168 
#define  HFI_PROPERTY_PARAM_VDEC_SCS_THRESHOLD 167 
#define  HFI_PROPERTY_PARAM_VDEC_THUMBNAIL_MODE 166 
#define  HFI_PROPERTY_PARAM_VENC_DISABLE_RC_TIMESTAMP 165 
#define  HFI_PROPERTY_PARAM_VENC_H264_DEBLOCK_CONTROL 164 
#define  HFI_PROPERTY_PARAM_VENC_H264_ENTROPY_CONTROL 163 
#define  HFI_PROPERTY_PARAM_VENC_H264_GENERATE_AUDNAL 162 
#define  HFI_PROPERTY_PARAM_VENC_H264_NAL_SVC_EXT 161 
#define  HFI_PROPERTY_PARAM_VENC_H264_VUI_BITSTREAM_RESTRC 160 
#define  HFI_PROPERTY_PARAM_VENC_H264_VUI_TIMING_INFO 159 
#define  HFI_PROPERTY_PARAM_VENC_HIER_B_MAX_NUM_ENH_LAYER 158 
#define  HFI_PROPERTY_PARAM_VENC_HIER_P_HYBRID_MODE 157 
#define  HFI_PROPERTY_PARAM_VENC_HIER_P_MAX_NUM_ENH_LAYER 156 
#define  HFI_PROPERTY_PARAM_VENC_INITIAL_QP 155 
#define  HFI_PROPERTY_PARAM_VENC_INTRA_REFRESH 154 
#define  HFI_PROPERTY_PARAM_VENC_LTRMODE 153 
#define  HFI_PROPERTY_PARAM_VENC_MAX_NUM_B_FRAMES 152 
#define  HFI_PROPERTY_PARAM_VENC_MPEG4_AC_PREDICTION 151 
#define  HFI_PROPERTY_PARAM_VENC_MPEG4_HEADER_EXTENSION 150 
#define  HFI_PROPERTY_PARAM_VENC_MPEG4_SHORT_HEADER 149 
#define  HFI_PROPERTY_PARAM_VENC_MPEG4_TIME_RESOLUTION 148 
#define  HFI_PROPERTY_PARAM_VENC_MULTI_SLICE_CONTROL 147 
#define  HFI_PROPERTY_PARAM_VENC_MULTI_SLICE_INFO 146 
#define  HFI_PROPERTY_PARAM_VENC_PRESERVE_TEXT_QUALITY 145 
#define  HFI_PROPERTY_PARAM_VENC_RATE_CONTROL 144 
#define  HFI_PROPERTY_PARAM_VENC_SESSION_QP 143 
#define  HFI_PROPERTY_PARAM_VENC_SESSION_QP_RANGE 142 
#define  HFI_PROPERTY_PARAM_VENC_SLICE_DELIVERY_MODE 141 
#define  HFI_PROPERTY_PARAM_VENC_VC1_PERF_CFG 140 
#define  HFI_PROPERTY_PARAM_VENC_VPX_ERROR_RESILIENCE_MODE 139 
#define  HFI_PROPERTY_PARAM_VPE_COLOR_SPACE_CONVERSION 138 
#define  HFI_PROPERTY_SYS_IDLE_INDICATOR 137 
#define  HFI_RATE_CONTROL_CBR_CFR 136 
#define  HFI_RATE_CONTROL_CBR_VFR 135 
#define  HFI_RATE_CONTROL_OFF 134 
#define  HFI_RATE_CONTROL_VBR_CFR 133 
#define  HFI_RATE_CONTROL_VBR_VFR 132 
#define  HFI_ROTATE_180 131 
#define  HFI_ROTATE_270 130 
#define  HFI_ROTATE_90 129 
#define  HFI_ROTATE_NONE 128 
 int /*<<< orphan*/  hash32_ptr (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pkt_session_set_property_1x(struct hfi_session_set_property_pkt *pkt,
				       void *cookie, u32 ptype, void *pdata)
{
	void *prop_data;
	int ret = 0;

	if (!pkt || !cookie || !pdata)
		return -EINVAL;

	prop_data = &pkt->data[1];

	pkt->shdr.hdr.size = sizeof(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_SET_PROPERTY;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->num_properties = 1;
	pkt->data[0] = ptype;

	switch (ptype) {
	case HFI_PROPERTY_CONFIG_FRAME_RATE: {
		struct hfi_framerate *in = pdata, *frate = prop_data;

		frate->buffer_type = in->buffer_type;
		frate->framerate = in->framerate;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*frate);
		break;
	}
	case HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SELECT: {
		struct hfi_uncompressed_format_select *in = pdata;
		struct hfi_uncompressed_format_select *hfi = prop_data;

		hfi->buffer_type = in->buffer_type;
		hfi->format = in->format;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*hfi);
		break;
	}
	case HFI_PROPERTY_PARAM_FRAME_SIZE: {
		struct hfi_framesize *in = pdata, *fsize = prop_data;

		fsize->buffer_type = in->buffer_type;
		fsize->height = in->height;
		fsize->width = in->width;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*fsize);
		break;
	}
	case HFI_PROPERTY_CONFIG_REALTIME: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) * 2;
		break;
	}
	case HFI_PROPERTY_PARAM_BUFFER_COUNT_ACTUAL: {
		struct hfi_buffer_count_actual *in = pdata, *count = prop_data;

		count->count_actual = in->count_actual;
		count->type = in->type;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*count);
		break;
	}
	case HFI_PROPERTY_PARAM_BUFFER_SIZE_ACTUAL: {
		struct hfi_buffer_size_actual *in = pdata, *sz = prop_data;

		sz->size = in->size;
		sz->type = in->type;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*sz);
		break;
	}
	case HFI_PROPERTY_PARAM_BUFFER_DISPLAY_HOLD_COUNT_ACTUAL: {
		struct hfi_buffer_display_hold_count_actual *in = pdata;
		struct hfi_buffer_display_hold_count_actual *count = prop_data;

		count->hold_count = in->hold_count;
		count->type = in->type;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*count);
		break;
	}
	case HFI_PROPERTY_PARAM_NAL_STREAM_FORMAT_SELECT: {
		struct hfi_nal_stream_format_select *in = pdata;
		struct hfi_nal_stream_format_select *fmt = prop_data;

		fmt->format = in->format;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*fmt);
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_OUTPUT_ORDER: {
		u32 *in = pdata;

		switch (*in) {
		case HFI_OUTPUT_ORDER_DECODE:
		case HFI_OUTPUT_ORDER_DISPLAY:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += sizeof(u32) * 2;
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_PICTURE_TYPE_DECODE: {
		struct hfi_enable_picture *in = pdata, *en = prop_data;

		en->picture_type = in->picture_type;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_OUTPUT2_KEEP_ASPECT_RATIO: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_CONFIG_VDEC_POST_LOOP_DEBLOCKER: {
		struct hfi_enable *in = pdata;
		struct hfi_enable *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_MULTI_STREAM: {
		struct hfi_multi_stream *in = pdata, *multi = prop_data;

		multi->buffer_type = in->buffer_type;
		multi->enable = in->enable;
		multi->width = in->width;
		multi->height = in->height;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*multi);
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_DISPLAY_PICTURE_BUFFER_COUNT: {
		struct hfi_display_picture_buffer_count *in = pdata;
		struct hfi_display_picture_buffer_count *count = prop_data;

		count->count = in->count;
		count->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*count);
		break;
	}
	case HFI_PROPERTY_PARAM_DIVX_FORMAT: {
		u32 *in = pdata;

		switch (*in) {
		case HFI_DIVX_FORMAT_4:
		case HFI_DIVX_FORMAT_5:
		case HFI_DIVX_FORMAT_6:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += sizeof(u32) * 2;
		break;
	}
	case HFI_PROPERTY_CONFIG_VDEC_MB_ERROR_MAP_REPORTING: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_CONTINUE_DATA_TRANSFER: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_THUMBNAIL_MODE: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_CONFIG_VENC_SYNC_FRAME_SEQUENCE_HEADER: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_CONFIG_VENC_REQUEST_SYNC_FRAME:
		pkt->shdr.hdr.size += sizeof(u32);
		break;
	case HFI_PROPERTY_PARAM_VENC_MPEG4_SHORT_HEADER:
		break;
	case HFI_PROPERTY_PARAM_VENC_MPEG4_AC_PREDICTION:
		break;
	case HFI_PROPERTY_CONFIG_VENC_TARGET_BITRATE: {
		struct hfi_bitrate *in = pdata, *brate = prop_data;

		brate->bitrate = in->bitrate;
		brate->layer_id = in->layer_id;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*brate);
		break;
	}
	case HFI_PROPERTY_CONFIG_VENC_MAX_BITRATE: {
		struct hfi_bitrate *in = pdata, *hfi = prop_data;

		hfi->bitrate = in->bitrate;
		hfi->layer_id = in->layer_id;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*hfi);
		break;
	}
	case HFI_PROPERTY_PARAM_PROFILE_LEVEL_CURRENT: {
		struct hfi_profile_level *in = pdata, *pl = prop_data;

		pl->level = in->level;
		pl->profile = in->profile;
		if (pl->profile <= 0)
			/* Profile not supported, falling back to high */
			pl->profile = HFI_H264_PROFILE_HIGH;

		if (!pl->level)
			/* Level not supported, falling back to 1 */
			pl->level = 1;

		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*pl);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_H264_ENTROPY_CONTROL: {
		struct hfi_h264_entropy_control *in = pdata, *hfi = prop_data;

		hfi->entropy_mode = in->entropy_mode;
		if (hfi->entropy_mode == HFI_H264_ENTROPY_CABAC)
			hfi->cabac_model = in->cabac_model;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*hfi);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_RATE_CONTROL: {
		u32 *in = pdata;

		switch (*in) {
		case HFI_RATE_CONTROL_OFF:
		case HFI_RATE_CONTROL_CBR_CFR:
		case HFI_RATE_CONTROL_CBR_VFR:
		case HFI_RATE_CONTROL_VBR_CFR:
		case HFI_RATE_CONTROL_VBR_VFR:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += sizeof(u32) * 2;
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_MPEG4_TIME_RESOLUTION: {
		struct hfi_mpeg4_time_resolution *in = pdata, *res = prop_data;

		res->time_increment_resolution = in->time_increment_resolution;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*res);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_MPEG4_HEADER_EXTENSION: {
		struct hfi_mpeg4_header_extension *in = pdata, *ext = prop_data;

		ext->header_extension = in->header_extension;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*ext);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_H264_DEBLOCK_CONTROL: {
		struct hfi_h264_db_control *in = pdata, *db = prop_data;

		switch (in->mode) {
		case HFI_H264_DB_MODE_DISABLE:
		case HFI_H264_DB_MODE_SKIP_SLICE_BOUNDARY:
		case HFI_H264_DB_MODE_ALL_BOUNDARY:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		db->mode = in->mode;
		db->slice_alpha_offset = in->slice_alpha_offset;
		db->slice_beta_offset = in->slice_beta_offset;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*db);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_SESSION_QP: {
		struct hfi_quantization *in = pdata, *quant = prop_data;

		quant->qp_i = in->qp_i;
		quant->qp_p = in->qp_p;
		quant->qp_b = in->qp_b;
		quant->layer_id = in->layer_id;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*quant);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_SESSION_QP_RANGE: {
		struct hfi_quantization_range *in = pdata, *range = prop_data;
		u32 min_qp, max_qp;

		min_qp = in->min_qp;
		max_qp = in->max_qp;

		/* We'll be packing in the qp, so make sure we
		 * won't be losing data when masking
		 */
		if (min_qp > 0xff || max_qp > 0xff) {
			ret = -ERANGE;
			break;
		}

		/* When creating the packet, pack the qp value as
		 * 0xiippbb, where ii = qp range for I-frames,
		 * pp = qp range for P-frames, etc.
		 */
		range->min_qp = min_qp | min_qp << 8 | min_qp << 16;
		range->max_qp = max_qp | max_qp << 8 | max_qp << 16;
		range->layer_id = in->layer_id;

		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*range);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_VC1_PERF_CFG: {
		struct hfi_vc1e_perf_cfg_type *in = pdata, *perf = prop_data;

		memcpy(perf->search_range_x_subsampled,
		       in->search_range_x_subsampled,
		       sizeof(perf->search_range_x_subsampled));
		memcpy(perf->search_range_y_subsampled,
		       in->search_range_y_subsampled,
		       sizeof(perf->search_range_y_subsampled));

		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*perf);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_MAX_NUM_B_FRAMES: {
		struct hfi_max_num_b_frames *bframes = prop_data;
		u32 *in = pdata;

		bframes->max_num_b_frames = *in;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*bframes);
		break;
	}
	case HFI_PROPERTY_CONFIG_VENC_INTRA_PERIOD: {
		struct hfi_intra_period *in = pdata, *intra = prop_data;

		intra->pframes = in->pframes;
		intra->bframes = in->bframes;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*intra);
		break;
	}
	case HFI_PROPERTY_CONFIG_VENC_IDR_PERIOD: {
		struct hfi_idr_period *in = pdata, *idr = prop_data;

		idr->idr_period = in->idr_period;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*idr);
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_CONCEAL_COLOR: {
		struct hfi_conceal_color *color = prop_data;
		u32 *in = pdata;

		color->conceal_color = *in;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*color);
		break;
	}
	case HFI_PROPERTY_CONFIG_VPE_OPERATIONS: {
		struct hfi_operations_type *in = pdata, *ops = prop_data;

		switch (in->rotation) {
		case HFI_ROTATE_NONE:
		case HFI_ROTATE_90:
		case HFI_ROTATE_180:
		case HFI_ROTATE_270:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		switch (in->flip) {
		case HFI_FLIP_NONE:
		case HFI_FLIP_HORIZONTAL:
		case HFI_FLIP_VERTICAL:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		ops->rotation = in->rotation;
		ops->flip = in->flip;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*ops);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_INTRA_REFRESH: {
		struct hfi_intra_refresh *in = pdata, *intra = prop_data;

		switch (in->mode) {
		case HFI_INTRA_REFRESH_NONE:
		case HFI_INTRA_REFRESH_ADAPTIVE:
		case HFI_INTRA_REFRESH_CYCLIC:
		case HFI_INTRA_REFRESH_CYCLIC_ADAPTIVE:
		case HFI_INTRA_REFRESH_RANDOM:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		intra->mode = in->mode;
		intra->air_mbs = in->air_mbs;
		intra->air_ref = in->air_ref;
		intra->cir_mbs = in->cir_mbs;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*intra);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_MULTI_SLICE_CONTROL: {
		struct hfi_multi_slice_control *in = pdata, *multi = prop_data;

		switch (in->multi_slice) {
		case HFI_MULTI_SLICE_OFF:
		case HFI_MULTI_SLICE_GOB:
		case HFI_MULTI_SLICE_BY_MB_COUNT:
		case HFI_MULTI_SLICE_BY_BYTE_COUNT:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		multi->multi_slice = in->multi_slice;
		multi->slice_size = in->slice_size;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*multi);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_SLICE_DELIVERY_MODE: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_H264_VUI_TIMING_INFO: {
		struct hfi_h264_vui_timing_info *in = pdata, *vui = prop_data;

		vui->enable = in->enable;
		vui->fixed_framerate = in->fixed_framerate;
		vui->time_scale = in->time_scale;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*vui);
		break;
	}
	case HFI_PROPERTY_CONFIG_VPE_DEINTERLACE: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_H264_GENERATE_AUDNAL: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE: {
		struct hfi_buffer_alloc_mode *in = pdata, *mode = prop_data;

		mode->type = in->type;
		mode->mode = in->mode;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*mode);
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_FRAME_ASSEMBLY: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_H264_VUI_BITSTREAM_RESTRC: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_PRESERVE_TEXT_QUALITY: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_SCS_THRESHOLD: {
		struct hfi_scs_threshold *thres = prop_data;
		u32 *in = pdata;

		thres->threshold_value = *in;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*thres);
		break;
	}
	case HFI_PROPERTY_PARAM_MVC_BUFFER_LAYOUT: {
		struct hfi_mvc_buffer_layout_descp_type *in = pdata;
		struct hfi_mvc_buffer_layout_descp_type *mvc = prop_data;

		switch (in->layout_type) {
		case HFI_MVC_BUFFER_LAYOUT_TOP_BOTTOM:
		case HFI_MVC_BUFFER_LAYOUT_SEQ:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		mvc->layout_type = in->layout_type;
		mvc->bright_view_first = in->bright_view_first;
		mvc->ngap = in->ngap;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*mvc);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_LTRMODE: {
		struct hfi_ltr_mode *in = pdata, *ltr = prop_data;

		switch (in->ltr_mode) {
		case HFI_LTR_MODE_DISABLE:
		case HFI_LTR_MODE_MANUAL:
		case HFI_LTR_MODE_PERIODIC:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		ltr->ltr_mode = in->ltr_mode;
		ltr->ltr_count = in->ltr_count;
		ltr->trust_mode = in->trust_mode;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*ltr);
		break;
	}
	case HFI_PROPERTY_CONFIG_VENC_USELTRFRAME: {
		struct hfi_ltr_use *in = pdata, *ltr_use = prop_data;

		ltr_use->frames = in->frames;
		ltr_use->ref_ltr = in->ref_ltr;
		ltr_use->use_constrnt = in->use_constrnt;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*ltr_use);
		break;
	}
	case HFI_PROPERTY_CONFIG_VENC_MARKLTRFRAME: {
		struct hfi_ltr_mark *in = pdata, *ltr_mark = prop_data;

		ltr_mark->mark_frame = in->mark_frame;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*ltr_mark);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_HIER_P_MAX_NUM_ENH_LAYER: {
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += sizeof(u32) * 2;
		break;
	}
	case HFI_PROPERTY_CONFIG_VENC_HIER_P_ENH_LAYER: {
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += sizeof(u32) * 2;
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_DISABLE_RC_TIMESTAMP: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_INITIAL_QP: {
		struct hfi_initial_quantization *in = pdata, *quant = prop_data;

		quant->init_qp_enable = in->init_qp_enable;
		quant->qp_i = in->qp_i;
		quant->qp_p = in->qp_p;
		quant->qp_b = in->qp_b;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*quant);
		break;
	}
	case HFI_PROPERTY_PARAM_VPE_COLOR_SPACE_CONVERSION: {
		struct hfi_vpe_color_space_conversion *in = pdata;
		struct hfi_vpe_color_space_conversion *csc = prop_data;

		memcpy(csc->csc_matrix, in->csc_matrix,
		       sizeof(csc->csc_matrix));
		memcpy(csc->csc_bias, in->csc_bias, sizeof(csc->csc_bias));
		memcpy(csc->csc_limit, in->csc_limit, sizeof(csc->csc_limit));
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*csc);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_VPX_ERROR_RESILIENCE_MODE: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_H264_NAL_SVC_EXT: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_CONFIG_VENC_PERF_MODE: {
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += sizeof(u32) * 2;
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_HIER_B_MAX_NUM_ENH_LAYER: {
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += sizeof(u32) * 2;
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_NONCP_OUTPUT2: {
		struct hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*en);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_HIER_P_HYBRID_MODE: {
		struct hfi_hybrid_hierp *in = pdata, *hierp = prop_data;

		hierp->layers = in->layers;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*hierp);
		break;
	}

	/* FOLLOWING PROPERTIES ARE NOT IMPLEMENTED IN CORE YET */
	case HFI_PROPERTY_CONFIG_BUFFER_REQUIREMENTS:
	case HFI_PROPERTY_CONFIG_PRIORITY:
	case HFI_PROPERTY_CONFIG_BATCH_INFO:
	case HFI_PROPERTY_SYS_IDLE_INDICATOR:
	case HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SUPPORTED:
	case HFI_PROPERTY_PARAM_INTERLACE_FORMAT_SUPPORTED:
	case HFI_PROPERTY_PARAM_CHROMA_SITE:
	case HFI_PROPERTY_PARAM_PROPERTIES_SUPPORTED:
	case HFI_PROPERTY_PARAM_PROFILE_LEVEL_SUPPORTED:
	case HFI_PROPERTY_PARAM_CAPABILITY_SUPPORTED:
	case HFI_PROPERTY_PARAM_NAL_STREAM_FORMAT_SUPPORTED:
	case HFI_PROPERTY_PARAM_MULTI_VIEW_FORMAT:
	case HFI_PROPERTY_PARAM_MAX_SEQUENCE_HEADER_SIZE:
	case HFI_PROPERTY_PARAM_CODEC_SUPPORTED:
	case HFI_PROPERTY_PARAM_VDEC_MULTI_VIEW_SELECT:
	case HFI_PROPERTY_PARAM_VDEC_MB_QUANTIZATION:
	case HFI_PROPERTY_PARAM_VDEC_NUM_CONCEALED_MB:
	case HFI_PROPERTY_PARAM_VDEC_H264_ENTROPY_SWITCHING:
	case HFI_PROPERTY_PARAM_VENC_MULTI_SLICE_INFO:
	default:
		return -EINVAL;
	}

	return ret;
}