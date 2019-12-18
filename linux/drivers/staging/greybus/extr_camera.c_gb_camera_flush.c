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
typedef  int /*<<< orphan*/  u32 ;
struct gb_camera_flush_response {int /*<<< orphan*/  request_id; } ;
struct gb_camera {int /*<<< orphan*/  mutex; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GB_CAMERA_TYPE_FLUSH ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_camera_flush_response*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_camera_flush(struct gb_camera *gcam, u32 *request_id)
{
	struct gb_camera_flush_response resp;
	int ret;

	mutex_lock(&gcam->mutex);

	if (!gcam->connection) {
		ret = -EINVAL;
		goto done;
	}

	ret = gb_operation_sync(gcam->connection, GB_CAMERA_TYPE_FLUSH, NULL, 0,
				&resp, sizeof(resp));

	if (ret < 0)
		goto done;

	if (request_id)
		*request_id = le32_to_cpu(resp.request_id);

done:
	mutex_unlock(&gcam->mutex);

	return ret;
}