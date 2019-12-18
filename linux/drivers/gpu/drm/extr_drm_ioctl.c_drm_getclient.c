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
struct drm_file {int /*<<< orphan*/  authenticated; } ;
struct drm_device {int dummy; } ;
struct drm_client {scalar_t__ idx; scalar_t__ iocs; scalar_t__ magic; int /*<<< orphan*/  uid; int /*<<< orphan*/  pid; int /*<<< orphan*/  auth; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  overflowuid ; 
 int /*<<< orphan*/  task_pid_vnr (int /*<<< orphan*/ ) ; 

int drm_getclient(struct drm_device *dev, void *data,
		  struct drm_file *file_priv)
{
	struct drm_client *client = data;

	/*
	 * Hollowed-out getclient ioctl to keep some dead old drm tests/tools
	 * not breaking completely. Userspace tools stop enumerating one they
	 * get -EINVAL, hence this is the return value we need to hand back for
	 * no clients tracked.
	 *
	 * Unfortunately some clients (*cough* libva *cough*) use this in a fun
	 * attempt to figure out whether they're authenticated or not. Since
	 * that's the only thing they care about, give it to the directly
	 * instead of walking one giant list.
	 */
	if (client->idx == 0) {
		client->auth = file_priv->authenticated;
		client->pid = task_pid_vnr(current);
		client->uid = overflowuid;
		client->magic = 0;
		client->iocs = 0;

		return 0;
	} else {
		return -EINVAL;
	}
}