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
struct intel_th_output {scalar_t__ multiblock; } ;
struct gth_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ REG_GTH_SCR ; 
 scalar_t__ REG_GTH_SCR2 ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void intel_th_gth_start(struct gth_device *gth,
			       struct intel_th_output *output)
{
	u32 scr = 0xfc0000;

	if (output->multiblock)
		scr |= 0xff;

	iowrite32(scr, gth->base + REG_GTH_SCR);
	iowrite32(0, gth->base + REG_GTH_SCR2);
}