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
struct qxl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,unsigned long) ; 

__attribute__((used)) static inline void *
qxl_fb_virtual_address(struct qxl_device *qdev, unsigned long physical)
{
	DRM_DEBUG_DRIVER("not implemented (%lu)\n", physical);
	return 0;
}