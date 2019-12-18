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
struct hdmi_drm_infoframe {int dummy; } ;
struct drm_connector_state {TYPE_1__* connector; int /*<<< orphan*/  hdr_output_metadata; } ;
struct dc_info_packet {int hb0; int hb1; int hb2; unsigned char* sb; int hb3; int valid; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int connector_type; } ;

/* Variables and functions */
#define  DRM_MODE_CONNECTOR_DisplayPort 130 
#define  DRM_MODE_CONNECTOR_HDMIA 129 
#define  DRM_MODE_CONNECTOR_eDP 128 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int drm_hdmi_infoframe_set_hdr_metadata (struct hdmi_drm_infoframe*,struct drm_connector_state const*) ; 
 int hdmi_drm_infoframe_pack_only (struct hdmi_drm_infoframe*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (struct dc_info_packet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int*,int,int) ; 

__attribute__((used)) static int fill_hdr_info_packet(const struct drm_connector_state *state,
				struct dc_info_packet *out)
{
	struct hdmi_drm_infoframe frame;
	unsigned char buf[30]; /* 26 + 4 */
	ssize_t len;
	int ret, i;

	memset(out, 0, sizeof(*out));

	if (!state->hdr_output_metadata)
		return 0;

	ret = drm_hdmi_infoframe_set_hdr_metadata(&frame, state);
	if (ret)
		return ret;

	len = hdmi_drm_infoframe_pack_only(&frame, buf, sizeof(buf));
	if (len < 0)
		return (int)len;

	/* Static metadata is a fixed 26 bytes + 4 byte header. */
	if (len != 30)
		return -EINVAL;

	/* Prepare the infopacket for DC. */
	switch (state->connector->connector_type) {
	case DRM_MODE_CONNECTOR_HDMIA:
		out->hb0 = 0x87; /* type */
		out->hb1 = 0x01; /* version */
		out->hb2 = 0x1A; /* length */
		out->sb[0] = buf[3]; /* checksum */
		i = 1;
		break;

	case DRM_MODE_CONNECTOR_DisplayPort:
	case DRM_MODE_CONNECTOR_eDP:
		out->hb0 = 0x00; /* sdp id, zero */
		out->hb1 = 0x87; /* type */
		out->hb2 = 0x1D; /* payload len - 1 */
		out->hb3 = (0x13 << 2); /* sdp version */
		out->sb[0] = 0x01; /* version */
		out->sb[1] = 0x1A; /* length */
		i = 2;
		break;

	default:
		return -EINVAL;
	}

	memcpy(&out->sb[i], &buf[4], 26);
	out->valid = true;

	print_hex_dump(KERN_DEBUG, "HDR SB:", DUMP_PREFIX_NONE, 16, 1, out->sb,
		       sizeof(out->sb), false);

	return 0;
}