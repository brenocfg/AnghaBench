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
struct dw_mipi_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_INT_MSK0 ; 
 int /*<<< orphan*/  DSI_INT_MSK1 ; 
 int /*<<< orphan*/  DSI_INT_ST0 ; 
 int /*<<< orphan*/  DSI_INT_ST1 ; 
 int /*<<< orphan*/  dsi_read (struct dw_mipi_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mipi_dsi_clear_err(struct dw_mipi_dsi *dsi)
{
	dsi_read(dsi, DSI_INT_ST0);
	dsi_read(dsi, DSI_INT_ST1);
	dsi_write(dsi, DSI_INT_MSK0, 0);
	dsi_write(dsi, DSI_INT_MSK1, 0);
}