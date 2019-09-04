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
struct file {int f_flags; int /*<<< orphan*/  f_mode; struct drm_file* private_data; } ;
struct drm_minor {int /*<<< orphan*/  index; struct drm_device* dev; } ;
struct drm_file {int /*<<< orphan*/  lhead; struct file* filp; } ;
struct drm_device {scalar_t__ switch_power_state; int /*<<< orphan*/  filelist_mutex; int /*<<< orphan*/  filelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DRM_SWITCH_POWER_DYNAMIC_OFF ; 
 scalar_t__ DRM_SWITCH_POWER_ON ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  FMODE_UNSIGNED_OFFSET ; 
 scalar_t__ IS_ERR (struct drm_file*) ; 
 int O_EXCL ; 
 int PTR_ERR (struct drm_file*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  drm_cpu_valid () ; 
 struct drm_file* drm_file_alloc (struct drm_minor*) ; 
 int /*<<< orphan*/  drm_file_free (struct drm_file*) ; 
 scalar_t__ drm_is_primary_client (struct drm_file*) ; 
 int drm_master_open (struct drm_file*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_open_helper(struct file *filp, struct drm_minor *minor)
{
	struct drm_device *dev = minor->dev;
	struct drm_file *priv;
	int ret;

	if (filp->f_flags & O_EXCL)
		return -EBUSY;	/* No exclusive opens */
	if (!drm_cpu_valid())
		return -EINVAL;
	if (dev->switch_power_state != DRM_SWITCH_POWER_ON && dev->switch_power_state != DRM_SWITCH_POWER_DYNAMIC_OFF)
		return -EINVAL;

	DRM_DEBUG("pid = %d, minor = %d\n", task_pid_nr(current), minor->index);

	priv = drm_file_alloc(minor);
	if (IS_ERR(priv))
		return PTR_ERR(priv);

	if (drm_is_primary_client(priv)) {
		ret = drm_master_open(priv);
		if (ret) {
			drm_file_free(priv);
			return ret;
		}
	}

	filp->private_data = priv;
	filp->f_mode |= FMODE_UNSIGNED_OFFSET;
	priv->filp = filp;

	mutex_lock(&dev->filelist_mutex);
	list_add(&priv->lhead, &dev->filelist);
	mutex_unlock(&dev->filelist_mutex);

#ifdef __alpha__
	/*
	 * Default the hose
	 */
	if (!dev->hose) {
		struct pci_dev *pci_dev;
		pci_dev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, NULL);
		if (pci_dev) {
			dev->hose = pci_dev->sysdata;
			pci_dev_put(pci_dev);
		}
		if (!dev->hose) {
			struct pci_bus *b = list_entry(pci_root_buses.next,
				struct pci_bus, node);
			if (b)
				dev->hose = b->sysdata;
		}
	}
#endif

	return 0;
}