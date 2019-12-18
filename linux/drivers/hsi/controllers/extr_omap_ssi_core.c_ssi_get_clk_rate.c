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
struct omap_ssi_controller {int /*<<< orphan*/  fck; } ;
struct hsi_controller {int dummy; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 struct omap_ssi_controller* hsi_controller_drvdata (struct hsi_controller*) ; 

__attribute__((used)) static unsigned long ssi_get_clk_rate(struct hsi_controller *ssi)
{
	struct omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	unsigned long rate = clk_get_rate(omap_ssi->fck);
	return rate;
}