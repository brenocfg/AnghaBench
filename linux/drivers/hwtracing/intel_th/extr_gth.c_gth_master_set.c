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
 unsigned int REG_GTH_GSWTDEST ; 
 unsigned int REG_GTH_SWDEST0 ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void
gth_master_set(struct gth_device *gth, unsigned int master, int port)
{
	unsigned int reg = REG_GTH_SWDEST0 + ((master >> 1) & ~3u);
	unsigned int shift = (master & 0x7) * 4;
	u32 val;

	if (master >= 256) {
		reg = REG_GTH_GSWTDEST;
		shift = 0;
	}

	val = ioread32(gth->base + reg);
	val &= ~(0xf << shift);
	if (port >= 0)
		val |= (0x8 | port) << shift;
	iowrite32(val, gth->base + reg);
}