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
struct vc4_dsi {int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 

__attribute__((used)) static void dsi_handle_error(struct vc4_dsi *dsi,
			     irqreturn_t *ret, u32 stat, u32 bit,
			     const char *type)
{
	if (!(stat & bit))
		return;

	DRM_ERROR("DSI%d: %s error\n", dsi->port, type);
	*ret = IRQ_HANDLED;
}