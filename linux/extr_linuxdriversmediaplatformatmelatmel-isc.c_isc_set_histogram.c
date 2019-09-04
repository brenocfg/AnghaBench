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
struct regmap {int dummy; } ;
struct isc_ctrls {scalar_t__ hist_stat; int hist_id; scalar_t__ awb; } ;
struct isc_device {TYPE_1__* raw_fmt; struct isc_ctrls ctrls; struct regmap* regmap; } ;
struct fmt_config {int cfa_baycfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 scalar_t__ HIST_DISABLED ; 
 scalar_t__ HIST_ENABLED ; 
 int /*<<< orphan*/  ISC_CTRLEN ; 
 int ISC_CTRL_HISREQ ; 
 int /*<<< orphan*/  ISC_HIS_CFG ; 
 int ISC_HIS_CFG_BAYSEL_SHIFT ; 
 int ISC_HIS_CFG_MODE_R ; 
 int ISC_HIS_CFG_RAR ; 
 int /*<<< orphan*/  ISC_HIS_CTRL ; 
 int ISC_HIS_CTRL_DIS ; 
 int ISC_HIS_CTRL_EN ; 
 int /*<<< orphan*/  ISC_INTDIS ; 
 int /*<<< orphan*/  ISC_INTEN ; 
 int ISC_INT_HISDONE ; 
 struct fmt_config* get_fmt_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_update_profile (struct isc_device*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isc_set_histogram(struct isc_device *isc)
{
	struct regmap *regmap = isc->regmap;
	struct isc_ctrls *ctrls = &isc->ctrls;
	struct fmt_config *config = get_fmt_config(isc->raw_fmt->fourcc);

	if (ctrls->awb && (ctrls->hist_stat != HIST_ENABLED)) {
		regmap_write(regmap, ISC_HIS_CFG,
			     ISC_HIS_CFG_MODE_R |
			     (config->cfa_baycfg << ISC_HIS_CFG_BAYSEL_SHIFT) |
			     ISC_HIS_CFG_RAR);
		regmap_write(regmap, ISC_HIS_CTRL, ISC_HIS_CTRL_EN);
		regmap_write(regmap, ISC_INTEN, ISC_INT_HISDONE);
		ctrls->hist_id = ISC_HIS_CFG_MODE_R;
		isc_update_profile(isc);
		regmap_write(regmap, ISC_CTRLEN, ISC_CTRL_HISREQ);

		ctrls->hist_stat = HIST_ENABLED;
	} else if (!ctrls->awb && (ctrls->hist_stat != HIST_DISABLED)) {
		regmap_write(regmap, ISC_INTDIS, ISC_INT_HISDONE);
		regmap_write(regmap, ISC_HIS_CTRL, ISC_HIS_CTRL_DIS);

		ctrls->hist_stat = HIST_DISABLED;
	}
}