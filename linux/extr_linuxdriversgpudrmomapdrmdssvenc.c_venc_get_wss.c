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
struct venc_device {int wss_data; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 struct venc_device* dssdev_to_venc (struct omap_dss_device*) ; 

__attribute__((used)) static u32 venc_get_wss(struct omap_dss_device *dssdev)
{
	struct venc_device *venc = dssdev_to_venc(dssdev);

	/* Invert due to VENC_L21_WC_CTL:INV=1 */
	return (venc->wss_data >> 8) ^ 0xfffff;
}