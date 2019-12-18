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
struct gb_camera_stream_config_response {scalar_t__ padding; } ;
struct gb_camera_configure_streams_response {unsigned int num_streams; struct gb_camera_stream_config_response* config; scalar_t__* padding; } ;
struct gb_camera {int dummy; } ;

/* Variables and functions */
 int const EIO ; 
 int /*<<< orphan*/  gcam_err (struct gb_camera*,char*,...) ; 

__attribute__((used)) static const int gb_camera_configure_streams_validate_response(
		struct gb_camera *gcam,
		struct gb_camera_configure_streams_response *resp,
		unsigned int nstreams)
{
	unsigned int i;

	/* Validate the returned response structure */
	if (resp->padding[0] || resp->padding[1]) {
		gcam_err(gcam, "response padding != 0\n");
		return -EIO;
	}

	if (resp->num_streams > nstreams) {
		gcam_err(gcam, "got #streams %u > request %u\n",
			 resp->num_streams, nstreams);
		return -EIO;
	}

	for (i = 0; i < resp->num_streams; i++) {
		struct gb_camera_stream_config_response *cfg = &resp->config[i];

		if (cfg->padding) {
			gcam_err(gcam, "stream #%u padding != 0\n", i);
			return -EIO;
		}
	}

	return 0;
}