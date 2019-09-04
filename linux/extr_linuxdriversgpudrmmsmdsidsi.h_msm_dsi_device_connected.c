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
struct msm_dsi {scalar_t__ external_bridge; scalar_t__ panel; } ;

/* Variables and functions */

__attribute__((used)) static inline bool msm_dsi_device_connected(struct msm_dsi *msm_dsi)
{
	return msm_dsi->panel || msm_dsi->external_bridge;
}