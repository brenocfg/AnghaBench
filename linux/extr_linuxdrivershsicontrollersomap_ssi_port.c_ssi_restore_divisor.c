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
struct TYPE_2__ {int /*<<< orphan*/  divisor; } ;
struct omap_ssi_port {scalar_t__ sst_base; TYPE_1__ sst; } ;

/* Variables and functions */
 scalar_t__ SSI_SST_DIVISOR_REG ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ssi_restore_divisor(struct omap_ssi_port *omap_port)
{
	writel_relaxed(omap_port->sst.divisor,
				omap_port->sst_base + SSI_SST_DIVISOR_REG);

	return 0;
}