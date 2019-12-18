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
struct drm_file {int dummy; } ;
struct drm_device {scalar_t__ dev_private; } ;
typedef  int /*<<< orphan*/  drm_i810_private_t ;

/* Variables and functions */
 int I810_READ (int) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 

__attribute__((used)) static int i810_fstatus(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	drm_i810_private_t *dev_priv = (drm_i810_private_t *) dev->dev_private;

	LOCK_TEST_WITH_RETURN(dev, file_priv);
	return I810_READ(0x30008);
}