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
struct gb_camera {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int gb_camera_capture (struct gb_camera*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kstrtouint (char*,int,unsigned int*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static ssize_t gb_camera_debugfs_capture(struct gb_camera *gcam,
					 char *buf, size_t len)
{
	unsigned int request_id;
	unsigned int streams_mask;
	unsigned int num_frames;
	char *token;
	int ret;

	/* Request id */
	token = strsep(&buf, ";");
	if (!token)
		return -EINVAL;
	ret = kstrtouint(token, 10, &request_id);
	if (ret < 0)
		return ret;

	/* Stream mask */
	token = strsep(&buf, ";");
	if (!token)
		return -EINVAL;
	ret = kstrtouint(token, 16, &streams_mask);
	if (ret < 0)
		return ret;

	/* number of frames */
	token = strsep(&buf, ";");
	if (!token)
		return -EINVAL;
	ret = kstrtouint(token, 10, &num_frames);
	if (ret < 0)
		return ret;

	ret = gb_camera_capture(gcam, request_id, streams_mask, num_frames, 0,
				NULL);
	if (ret < 0)
		return ret;

	return len;
}