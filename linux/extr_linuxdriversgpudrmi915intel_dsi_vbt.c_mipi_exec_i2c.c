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
typedef  int u8 ;
struct intel_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 

__attribute__((used)) static const u8 *mipi_exec_i2c(struct intel_dsi *intel_dsi, const u8 *data)
{
	DRM_DEBUG_KMS("Skipping I2C element execution\n");

	return data + *(data + 6) + 7;
}