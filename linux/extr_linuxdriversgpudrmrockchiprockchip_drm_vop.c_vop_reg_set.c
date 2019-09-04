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
typedef  int uint32_t ;
struct vop_reg {int mask; int offset; int shift; scalar_t__ relaxed; scalar_t__ write_mask; } ;
struct vop {int* regsbak; scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void vop_reg_set(struct vop *vop, const struct vop_reg *reg,
			uint32_t _offset, uint32_t _mask, uint32_t v,
			const char *reg_name)
{
	int offset, mask, shift;

	if (!reg || !reg->mask) {
		DRM_DEV_DEBUG(vop->dev, "Warning: not support %s\n", reg_name);
		return;
	}

	offset = reg->offset + _offset;
	mask = reg->mask & _mask;
	shift = reg->shift;

	if (reg->write_mask) {
		v = ((v << shift) & 0xffff) | (mask << (shift + 16));
	} else {
		uint32_t cached_val = vop->regsbak[offset >> 2];

		v = (cached_val & ~(mask << shift)) | ((v & mask) << shift);
		vop->regsbak[offset >> 2] = v;
	}

	if (reg->relaxed)
		writel_relaxed(v, vop->regs + offset);
	else
		writel(v, vop->regs + offset);
}