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
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  R128_CLOCK_CNTL_DATA ; 
 int /*<<< orphan*/  R128_CLOCK_CNTL_INDEX ; 
 int R128_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R128_WRITE8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int R128_READ_PLL(struct drm_device *dev, int addr)
{
	drm_r128_private_t *dev_priv = dev->dev_private;

	R128_WRITE8(R128_CLOCK_CNTL_INDEX, addr & 0x1f);
	return R128_READ(R128_CLOCK_CNTL_DATA);
}