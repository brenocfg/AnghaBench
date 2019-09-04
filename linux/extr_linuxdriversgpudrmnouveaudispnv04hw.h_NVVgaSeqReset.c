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
 int /*<<< orphan*/  NVWriteVgaSeq (struct drm_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NV_VIO_SR_RESET_INDEX ; 

__attribute__((used)) static inline void NVVgaSeqReset(struct drm_device *dev, int head, bool start)
{
	NVWriteVgaSeq(dev, head, NV_VIO_SR_RESET_INDEX, start ? 0x1 : 0x3);
}