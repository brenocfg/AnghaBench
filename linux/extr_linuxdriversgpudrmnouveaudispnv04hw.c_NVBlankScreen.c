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
struct drm_device {int dummy; } ;

/* Variables and functions */
 unsigned char NVReadVgaSeq (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVSetOwner (struct drm_device*,int) ; 
 int /*<<< orphan*/  NVVgaSeqReset (struct drm_device*,int,int) ; 
 int /*<<< orphan*/  NVWriteVgaSeq (struct drm_device*,int,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  NV_VIO_SR_CLOCK_INDEX ; 
 scalar_t__ nv_two_heads (struct drm_device*) ; 

void
NVBlankScreen(struct drm_device *dev, int head, bool blank)
{
	unsigned char seq1;

	if (nv_two_heads(dev))
		NVSetOwner(dev, head);

	seq1 = NVReadVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX);

	NVVgaSeqReset(dev, head, true);
	if (blank)
		NVWriteVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX, seq1 | 0x20);
	else
		NVWriteVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX, seq1 & ~0x20);
	NVVgaSeqReset(dev, head, false);
}