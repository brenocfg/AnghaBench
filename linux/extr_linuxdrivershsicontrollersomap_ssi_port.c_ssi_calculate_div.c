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
struct omap_ssi_controller {int max_speed; int /*<<< orphan*/  fck_rate; } ;
struct hsi_controller {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 struct omap_ssi_controller* hsi_controller_drvdata (struct hsi_controller*) ; 

__attribute__((used)) static u32 ssi_calculate_div(struct hsi_controller *ssi)
{
	struct omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	u32 tx_fckrate = (u32) omap_ssi->fck_rate;

	/* / 2 : SSI TX clock is always half of the SSI functional clock */
	tx_fckrate >>= 1;
	/* Round down when tx_fckrate % omap_ssi->max_speed == 0 */
	tx_fckrate--;
	dev_dbg(&ssi->device, "TX div %d for fck_rate %lu Khz speed %d Kb/s\n",
		tx_fckrate / omap_ssi->max_speed, omap_ssi->fck_rate,
		omap_ssi->max_speed);

	return tx_fckrate / omap_ssi->max_speed;
}