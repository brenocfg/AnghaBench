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
struct omap_vout_device {int rotation; int /*<<< orphan*/  mirror; } ;

/* Variables and functions */
 int dss_rotation_0_degree ; 
#define  dss_rotation_180_degree 130 
#define  dss_rotation_270_degree 129 
#define  dss_rotation_90_degree 128 

__attribute__((used)) static inline int calc_rotation(const struct omap_vout_device *vout)
{
	if (!vout->mirror)
		return vout->rotation;

	switch (vout->rotation) {
	case dss_rotation_90_degree:
		return dss_rotation_270_degree;
	case dss_rotation_270_degree:
		return dss_rotation_90_degree;
	case dss_rotation_180_degree:
		return dss_rotation_0_degree;
	default:
		return dss_rotation_180_degree;
	}
}