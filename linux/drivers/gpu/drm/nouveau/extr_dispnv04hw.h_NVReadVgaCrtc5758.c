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
typedef  int /*<<< orphan*/  uint8_t ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVReadVgaCrtc (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteVgaCrtc (struct drm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_CIO_CRE_57 ; 
 int /*<<< orphan*/  NV_CIO_CRE_58 ; 

__attribute__((used)) static inline uint8_t NVReadVgaCrtc5758(struct drm_device *dev, int head, uint8_t index)
{
	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_57, index);
	return NVReadVgaCrtc(dev, head, NV_CIO_CRE_58);
}