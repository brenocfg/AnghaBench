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
 int REG_GTH_SMCR0 ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void gth_smcfreq_set(struct gth_device *gth, int port,
			    unsigned int freq)
{
	unsigned long reg = REG_GTH_SMCR0 + ((port / 2) * 4);
	int shift = (port & 1) * 16;
	u32 val;

	val = ioread32(gth->base + reg);
	val &= ~(0xffff << shift);
	val |= freq << shift;
	iowrite32(val, gth->base + reg);
}