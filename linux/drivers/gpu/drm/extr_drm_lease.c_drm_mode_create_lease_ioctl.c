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
struct file {int /*<<< orphan*/  lessee_id; struct drm_file* private_data; scalar_t__ lessor; } ;
typedef  struct file uint32_t ;
struct idr {int dummy; } ;
struct drm_mode_create_lease {size_t object_count; int flags; int fd; int /*<<< orphan*/  lessee_id; int /*<<< orphan*/  object_ids; } ;
struct drm_master {int /*<<< orphan*/  lessee_id; struct drm_file* private_data; scalar_t__ lessor; } ;
struct drm_file {int is_master; int authenticated; struct file* master; struct file* filp; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG_LEASE (char*,...) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  array_size (size_t,int) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct file* drm_lease_create (struct file*,struct idr*) ; 
 int /*<<< orphan*/  drm_master_put (struct file**) ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 struct file* file_clone_open (struct file*) ; 
 int fill_object_idr (struct drm_device*,struct drm_file*,struct idr*,size_t,struct file*) ; 
 int get_unused_fd_flags (int) ; 
 int /*<<< orphan*/  idr_destroy (struct idr*) ; 
 int /*<<< orphan*/  idr_init (struct idr*) ; 
 int /*<<< orphan*/  kfree (struct file*) ; 
 struct file* memdup_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

int drm_mode_create_lease_ioctl(struct drm_device *dev,
				void *data, struct drm_file *lessor_priv)
{
	struct drm_mode_create_lease *cl = data;
	size_t object_count;
	int ret = 0;
	struct idr leases;
	struct drm_master *lessor = lessor_priv->master;
	struct drm_master *lessee = NULL;
	struct file *lessee_file = NULL;
	struct file *lessor_file = lessor_priv->filp;
	struct drm_file *lessee_priv;
	int fd = -1;
	uint32_t *object_ids;

	/* Can't lease without MODESET */
	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EOPNOTSUPP;

	/* Do not allow sub-leases */
	if (lessor->lessor) {
		DRM_DEBUG_LEASE("recursive leasing not allowed\n");
		return -EINVAL;
	}

	/* need some objects */
	if (cl->object_count == 0) {
		DRM_DEBUG_LEASE("no objects in lease\n");
		return -EINVAL;
	}

	if (cl->flags && (cl->flags & ~(O_CLOEXEC | O_NONBLOCK))) {
		DRM_DEBUG_LEASE("invalid flags\n");
		return -EINVAL;
	}

	object_count = cl->object_count;

	object_ids = memdup_user(u64_to_user_ptr(cl->object_ids),
			array_size(object_count, sizeof(__u32)));
	if (IS_ERR(object_ids))
		return PTR_ERR(object_ids);

	idr_init(&leases);

	/* fill and validate the object idr */
	ret = fill_object_idr(dev, lessor_priv, &leases,
			      object_count, object_ids);
	kfree(object_ids);
	if (ret) {
		DRM_DEBUG_LEASE("lease object lookup failed: %i\n", ret);
		idr_destroy(&leases);
		return ret;
	}

	/* Allocate a file descriptor for the lease */
	fd = get_unused_fd_flags(cl->flags & (O_CLOEXEC | O_NONBLOCK));
	if (fd < 0) {
		idr_destroy(&leases);
		return fd;
	}

	DRM_DEBUG_LEASE("Creating lease\n");
	lessee = drm_lease_create(lessor, &leases);

	if (IS_ERR(lessee)) {
		ret = PTR_ERR(lessee);
		goto out_leases;
	}

	/* Clone the lessor file to create a new file for us */
	DRM_DEBUG_LEASE("Allocating lease file\n");
	lessee_file = file_clone_open(lessor_file);
	if (IS_ERR(lessee_file)) {
		ret = PTR_ERR(lessee_file);
		goto out_lessee;
	}

	lessee_priv = lessee_file->private_data;
	/* Change the file to a master one */
	drm_master_put(&lessee_priv->master);
	lessee_priv->master = lessee;
	lessee_priv->is_master = 1;
	lessee_priv->authenticated = 1;

	/* Pass fd back to userspace */
	DRM_DEBUG_LEASE("Returning fd %d id %d\n", fd, lessee->lessee_id);
	cl->fd = fd;
	cl->lessee_id = lessee->lessee_id;

	/* Hook up the fd */
	fd_install(fd, lessee_file);

	DRM_DEBUG_LEASE("drm_mode_create_lease_ioctl succeeded\n");
	return 0;

out_lessee:
	drm_master_put(&lessee);

out_leases:
	put_unused_fd(fd);
	idr_destroy(&leases);

	DRM_DEBUG_LEASE("drm_mode_create_lease_ioctl failed: %d\n", ret);
	return ret;
}