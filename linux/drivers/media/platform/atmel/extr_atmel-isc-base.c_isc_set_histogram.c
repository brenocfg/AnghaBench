#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sd_format; } ;
struct isc_ctrls {int hist_id; int /*<<< orphan*/  hist_stat; } ;
struct isc_device {TYPE_2__ config; struct isc_ctrls ctrls; struct regmap* regmap; } ;
struct TYPE_3__ {int cfa_baycfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIST_DISABLED ; 
 int /*<<< orphan*/  HIST_ENABLED ; 
 int /*<<< orphan*/  ISC_CTRLEN ; 
 int ISC_CTRL_HISREQ ; 
 int /*<<< orphan*/  ISC_HIS_CFG ; 
 int ISC_HIS_CFG_BAYSEL_SHIFT ; 
 int ISC_HIS_CFG_MODE_GR ; 
 int ISC_HIS_CFG_RAR ; 
 int /*<<< orphan*/  ISC_HIS_CTRL ; 
 int ISC_HIS_CTRL_DIS ; 
 int ISC_HIS_CTRL_EN ; 
 int /*<<< orphan*/  ISC_INTDIS ; 
 int /*<<< orphan*/  ISC_INTEN ; 
 int ISC_INT_HISDONE ; 
 int /*<<< orphan*/  isc_update_profile (struct isc_device*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isc_set_histogram(struct isc_device *isc, bool enable)
{
	struct regmap *regmap = isc->regmap;
	struct isc_ctrls *ctrls = &isc->ctrls;

	if (enable) {
		regmap_write(regmap, ISC_HIS_CFG,
			     ISC_HIS_CFG_MODE_GR |
			     (isc->config.sd_format->cfa_baycfg
					<< ISC_HIS_CFG_BAYSEL_SHIFT) |
					ISC_HIS_CFG_RAR);
		regmap_write(regmap, ISC_HIS_CTRL, ISC_HIS_CTRL_EN);
		regmap_write(regmap, ISC_INTEN, ISC_INT_HISDONE);
		ctrls->hist_id = ISC_HIS_CFG_MODE_GR;
		isc_update_profile(isc);
		regmap_write(regmap, ISC_CTRLEN, ISC_CTRL_HISREQ);

		ctrls->hist_stat = HIST_ENABLED;
	} else {
		regmap_write(regmap, ISC_INTDIS, ISC_INT_HISDONE);
		regmap_write(regmap, ISC_HIS_CTRL, ISC_HIS_CTRL_DIS);

		ctrls->hist_stat = HIST_DISABLED;
	}
}