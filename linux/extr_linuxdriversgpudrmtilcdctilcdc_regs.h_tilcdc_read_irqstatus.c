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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tilcdc_irqstatus_reg (struct drm_device*) ; 
 int /*<<< orphan*/  tilcdc_read (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 tilcdc_read_irqstatus(struct drm_device *dev)
{
	return tilcdc_read(dev, tilcdc_irqstatus_reg(dev));
}