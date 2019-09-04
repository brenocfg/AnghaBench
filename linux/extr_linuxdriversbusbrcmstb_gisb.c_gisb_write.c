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
struct brcmstb_gisb_arb_device {int* gisb_offsets; scalar_t__ base; scalar_t__ big_endian; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void gisb_write(struct brcmstb_gisb_arb_device *gdev, u32 val, int reg)
{
	int offset = gdev->gisb_offsets[reg];

	if (offset == -1)
		return;

	if (gdev->big_endian)
		iowrite32be(val, gdev->base + offset);
	else
		iowrite32(val, gdev->base + offset);
}