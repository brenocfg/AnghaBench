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
struct omap_dss_device {int dummy; } ;
typedef  enum omap_dss_venc_type { ____Placeholder_omap_dss_venc_type } omap_dss_venc_type ;

/* Variables and functions */
 int OMAP_DSS_VENC_TYPE_COMPOSITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void opa362_set_type(struct omap_dss_device *dssdev,
		enum omap_dss_venc_type type)
{
	/* we can only drive a COMPOSITE output */
	WARN_ON(type != OMAP_DSS_VENC_TYPE_COMPOSITE);

}