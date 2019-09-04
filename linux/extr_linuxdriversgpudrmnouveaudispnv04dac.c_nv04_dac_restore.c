#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  output; } ;
struct nouveau_encoder {int /*<<< orphan*/  last_dpms; TYPE_1__ restore; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_DPMS_CLEARED ; 
 scalar_t__ NV_PRAMDAC_DACCLK ; 
 struct nouveau_encoder* nouveau_encoder (struct drm_encoder*) ; 
 scalar_t__ nv04_dac_output_offset (struct drm_encoder*) ; 
 scalar_t__ nv_gf4_disp_arch (struct drm_device*) ; 

__attribute__((used)) static void nv04_dac_restore(struct drm_encoder *encoder)
{
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	struct drm_device *dev = encoder->dev;

	if (nv_gf4_disp_arch(dev))
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + nv04_dac_output_offset(encoder),
			      nv_encoder->restore.output);

	nv_encoder->last_dpms = NV_DPMS_CLEARED;
}