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
struct malidp_drm {int core_id; } ;
struct drm_device {struct malidp_drm* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t core_id_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	struct drm_device *drm = dev_get_drvdata(dev);
	struct malidp_drm *malidp = drm->dev_private;

	return snprintf(buf, PAGE_SIZE, "%08x\n", malidp->core_id);
}