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
struct gb_camera_stream_config {int /*<<< orphan*/  format; int /*<<< orphan*/  max_size; int /*<<< orphan*/ * dt; int /*<<< orphan*/  vc; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct gb_camera_stream {int /*<<< orphan*/  pixel_code; int /*<<< orphan*/  max_size; int /*<<< orphan*/ * dt; int /*<<< orphan*/  vc; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct gb_camera_csi_params {int dummy; } ;
struct gb_camera {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int GB_CAMERA_CONFIGURE_STREAMS_ADJUSTED ; 
 unsigned int GB_CAMERA_CONFIGURE_STREAMS_TEST_ONLY ; 
 unsigned int GB_CAMERA_IN_FLAG_TEST ; 
 unsigned int GB_CAMERA_MAX_STREAMS ; 
 unsigned int GB_CAMERA_OUT_FLAG_ADJUSTED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int gb_camera_configure_streams (struct gb_camera*,unsigned int*,unsigned int*,struct gb_camera_stream_config*,struct gb_camera_csi_params*) ; 
 int /*<<< orphan*/  gb_camera_gb_to_mbus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_camera_mbus_to_gb (int /*<<< orphan*/ ) ; 
 struct gb_camera_stream_config* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gb_camera_stream_config*) ; 

__attribute__((used)) static int gb_camera_op_configure_streams(void *priv, unsigned int *nstreams,
		unsigned int *flags, struct gb_camera_stream *streams,
		struct gb_camera_csi_params *csi_params)
{
	struct gb_camera *gcam = priv;
	struct gb_camera_stream_config *gb_streams;
	unsigned int gb_flags = 0;
	unsigned int gb_nstreams = *nstreams;
	unsigned int i;
	int ret;

	if (gb_nstreams > GB_CAMERA_MAX_STREAMS)
		return -EINVAL;

	gb_streams = kcalloc(gb_nstreams, sizeof(*gb_streams), GFP_KERNEL);
	if (!gb_streams)
		return -ENOMEM;

	for (i = 0; i < gb_nstreams; i++) {
		gb_streams[i].width = streams[i].width;
		gb_streams[i].height = streams[i].height;
		gb_streams[i].format =
			gb_camera_mbus_to_gb(streams[i].pixel_code);
	}

	if (*flags & GB_CAMERA_IN_FLAG_TEST)
		gb_flags |= GB_CAMERA_CONFIGURE_STREAMS_TEST_ONLY;

	ret = gb_camera_configure_streams(gcam, &gb_nstreams,
					  &gb_flags, gb_streams, csi_params);
	if (ret < 0)
		goto done;
	if (gb_nstreams > *nstreams) {
		ret = -EINVAL;
		goto done;
	}

	*flags = 0;
	if (gb_flags & GB_CAMERA_CONFIGURE_STREAMS_ADJUSTED)
		*flags |= GB_CAMERA_OUT_FLAG_ADJUSTED;

	for (i = 0; i < gb_nstreams; i++) {
		streams[i].width = gb_streams[i].width;
		streams[i].height = gb_streams[i].height;
		streams[i].vc = gb_streams[i].vc;
		streams[i].dt[0] = gb_streams[i].dt[0];
		streams[i].dt[1] = gb_streams[i].dt[1];
		streams[i].max_size = gb_streams[i].max_size;
		streams[i].pixel_code =
			gb_camera_gb_to_mbus(gb_streams[i].format);
	}
	*nstreams = gb_nstreams;

done:
	kfree(gb_streams);
	return ret;
}