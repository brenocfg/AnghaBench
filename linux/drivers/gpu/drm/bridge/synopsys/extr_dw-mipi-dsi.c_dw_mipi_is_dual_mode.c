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
struct dw_mipi_dsi {scalar_t__ master; scalar_t__ slave; } ;

/* Variables and functions */

__attribute__((used)) static inline bool dw_mipi_is_dual_mode(struct dw_mipi_dsi *dsi)
{
	return dsi->slave || dsi->master;
}