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
typedef  int u32 ;
struct psb_intel_i2c_chan {int /*<<< orphan*/  reg; struct drm_device* drm_dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int GPIO_CLOCK_VAL_IN ; 
 int REG_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_clock(void *data)
{
	struct psb_intel_i2c_chan *chan = data;
	struct drm_device *dev = chan->drm_dev;
	u32 val;

	val = REG_READ(chan->reg);
	return (val & GPIO_CLOCK_VAL_IN) != 0;
}