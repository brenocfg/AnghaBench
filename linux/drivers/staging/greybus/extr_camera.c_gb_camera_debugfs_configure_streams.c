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
struct gb_camera_stream_config {unsigned int width; unsigned int height; unsigned int format; int vc; int* dt; int max_size; } ;
struct gb_camera_debugfs_buffer {scalar_t__ length; scalar_t__ data; } ;
struct TYPE_2__ {struct gb_camera_debugfs_buffer* buffers; } ;
struct gb_camera {TYPE_1__ debugfs; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 size_t GB_CAMERA_DEBUGFS_BUFFER_STREAMS ; 
 unsigned int GB_CAMERA_MAX_STREAMS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int gb_camera_configure_streams (struct gb_camera*,unsigned int*,unsigned int*,struct gb_camera_stream_config*,int /*<<< orphan*/ *) ; 
 struct gb_camera_stream_config* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gb_camera_stream_config*) ; 
 int kstrtouint (char*,int,unsigned int*) ; 
 scalar_t__ sprintf (scalar_t__,char*,unsigned int,unsigned int,...) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static ssize_t gb_camera_debugfs_configure_streams(struct gb_camera *gcam,
						   char *buf, size_t len)
{
	struct gb_camera_debugfs_buffer *buffer =
		&gcam->debugfs.buffers[GB_CAMERA_DEBUGFS_BUFFER_STREAMS];
	struct gb_camera_stream_config *streams;
	unsigned int nstreams;
	unsigned int flags;
	unsigned int i;
	char *token;
	int ret;

	/* Retrieve number of streams to configure */
	token = strsep(&buf, ";");
	if (!token)
		return -EINVAL;

	ret = kstrtouint(token, 10, &nstreams);
	if (ret < 0)
		return ret;

	if (nstreams > GB_CAMERA_MAX_STREAMS)
		return -EINVAL;

	token = strsep(&buf, ";");
	if (!token)
		return -EINVAL;

	ret = kstrtouint(token, 10, &flags);
	if (ret < 0)
		return ret;

	/* For each stream to configure parse width, height and format */
	streams = kcalloc(nstreams, sizeof(*streams), GFP_KERNEL);
	if (!streams)
		return -ENOMEM;

	for (i = 0; i < nstreams; ++i) {
		struct gb_camera_stream_config *stream = &streams[i];

		/* width */
		token = strsep(&buf, ";");
		if (!token) {
			ret = -EINVAL;
			goto done;
		}
		ret = kstrtouint(token, 10, &stream->width);
		if (ret < 0)
			goto done;

		/* height */
		token = strsep(&buf, ";");
		if (!token)
			goto done;

		ret = kstrtouint(token, 10, &stream->height);
		if (ret < 0)
			goto done;

		/* Image format code */
		token = strsep(&buf, ";");
		if (!token)
			goto done;

		ret = kstrtouint(token, 16, &stream->format);
		if (ret < 0)
			goto done;
	}

	ret = gb_camera_configure_streams(gcam, &nstreams, &flags, streams,
					  NULL);
	if (ret < 0)
		goto done;

	buffer->length = sprintf(buffer->data, "%u;%u;", nstreams, flags);

	for (i = 0; i < nstreams; ++i) {
		struct gb_camera_stream_config *stream = &streams[i];

		buffer->length += sprintf(buffer->data + buffer->length,
					  "%u;%u;%u;%u;%u;%u;%u;",
					  stream->width, stream->height,
					  stream->format, stream->vc,
					  stream->dt[0], stream->dt[1],
					  stream->max_size);
	}

	ret = len;

done:
	kfree(streams);
	return ret;
}