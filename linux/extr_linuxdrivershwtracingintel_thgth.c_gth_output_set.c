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
struct gth_device {scalar_t__ base; } ;

/* Variables and functions */
 unsigned long REG_GTH_GTHOPT0 ; 
 unsigned long REG_GTH_GTHOPT1 ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void gth_output_set(struct gth_device *gth, int port,
			   unsigned int config)
{
	unsigned long reg = port & 4 ? REG_GTH_GTHOPT1 : REG_GTH_GTHOPT0;
	u32 val;
	int shift = (port & 3) * 8;

	val = ioread32(gth->base + reg);
	val &= ~(0xff << shift);
	val |= config << shift;
	iowrite32(val, gth->base + reg);
}