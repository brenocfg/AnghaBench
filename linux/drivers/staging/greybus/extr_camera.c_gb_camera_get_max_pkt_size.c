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
struct gb_camera_stream_config_response {int /*<<< orphan*/  max_pkt_size; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct gb_camera_fmt_info {int bpp; } ;
struct gb_camera_configure_streams_response {unsigned int num_streams; struct gb_camera_stream_config_response* config; } ;
struct gb_camera {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 struct gb_camera_fmt_info* gb_camera_get_format_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcam_err (struct gb_camera*,char*,unsigned int,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,unsigned int) ; 

__attribute__((used)) static int gb_camera_get_max_pkt_size(struct gb_camera *gcam,
		struct gb_camera_configure_streams_response *resp)
{
	unsigned int max_pkt_size = 0;
	unsigned int i;

	for (i = 0; i < resp->num_streams; i++) {
		struct gb_camera_stream_config_response *cfg = &resp->config[i];
		const struct gb_camera_fmt_info *fmt_info;
		unsigned int pkt_size;

		fmt_info = gb_camera_get_format_info(cfg->format);
		if (!fmt_info) {
			gcam_err(gcam, "unsupported greybus image format: %d\n",
				 cfg->format);
			return -EIO;
		}

		if (fmt_info->bpp == 0) {
			pkt_size = le32_to_cpu(cfg->max_pkt_size);

			if (pkt_size == 0) {
				gcam_err(gcam,
					 "Stream %u: invalid zero maximum packet size\n",
					 i);
				return -EIO;
			}
		} else {
			pkt_size = le16_to_cpu(cfg->width) * fmt_info->bpp / 8;

			if (pkt_size != le32_to_cpu(cfg->max_pkt_size)) {
				gcam_err(gcam,
					 "Stream %u: maximum packet size mismatch (%u/%u)\n",
					 i, pkt_size, cfg->max_pkt_size);
				return -EIO;
			}
		}

		max_pkt_size = max(pkt_size, max_pkt_size);
	}

	return max_pkt_size;
}