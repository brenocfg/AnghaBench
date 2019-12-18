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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  bus_width; } ;
struct komeda_dev {TYPE_1__ chip; } ;
struct drm_mode_create_dumb {int width; int bpp; int /*<<< orphan*/  pitch; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct komeda_dev* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int drm_gem_cma_dumb_create_internal (struct drm_file*,struct drm_device*,struct drm_mode_create_dumb*) ; 

__attribute__((used)) static int komeda_gem_cma_dumb_create(struct drm_file *file,
				      struct drm_device *dev,
				      struct drm_mode_create_dumb *args)
{
	struct komeda_dev *mdev = dev->dev_private;
	u32 pitch = DIV_ROUND_UP(args->width * args->bpp, 8);

	args->pitch = ALIGN(pitch, mdev->chip.bus_width);

	return drm_gem_cma_dumb_create_internal(file, dev, args);
}