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
struct ubi_volume_info {int /*<<< orphan*/  used_bytes; int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ubi_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct gluebi_device {TYPE_1__ mtd; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  devices_mutex ; 
 int /*<<< orphan*/  err_msg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gluebi_device* find_gluebi_nolock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gluebi_resized(struct ubi_volume_info *vi)
{
	struct gluebi_device *gluebi;

	mutex_lock(&devices_mutex);
	gluebi = find_gluebi_nolock(vi->ubi_num, vi->vol_id);
	if (!gluebi) {
		mutex_unlock(&devices_mutex);
		err_msg("got update notification for unknown UBI device %d volume %d",
			vi->ubi_num, vi->vol_id);
		return -ENOENT;
	}
	gluebi->mtd.size = vi->used_bytes;
	mutex_unlock(&devices_mutex);
	return 0;
}