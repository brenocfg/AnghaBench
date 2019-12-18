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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_3__ {int options; scalar_t__ sff8472_compliance; int diagmon; } ;
struct TYPE_4__ {TYPE_1__ ext; } ;
struct sfp {int max_power_mW; int /*<<< orphan*/  dev; TYPE_2__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int SFP_DIAGMON_ADDRMODE ; 
 int SFP_DIAGMON_DDM ; 
 int /*<<< orphan*/  SFP_EXT_STATUS ; 
 int /*<<< orphan*/  SFP_OPTIONS_HIGH_POWER_LEVEL ; 
 int /*<<< orphan*/  SFP_OPTIONS_POWER_DECL ; 
 scalar_t__ SFP_SFF8472_COMPLIANCE_NONE ; 
 int T_HPOWER_LEVEL ; 
 int cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int sfp_read (struct sfp*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int sfp_write (struct sfp*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sfp_sm_mod_hpower(struct sfp *sfp)
{
	u32 power;
	u8 val;
	int err;

	power = 1000;
	if (sfp->id.ext.options & cpu_to_be16(SFP_OPTIONS_POWER_DECL))
		power = 1500;
	if (sfp->id.ext.options & cpu_to_be16(SFP_OPTIONS_HIGH_POWER_LEVEL))
		power = 2000;

	if (sfp->id.ext.sff8472_compliance == SFP_SFF8472_COMPLIANCE_NONE &&
	    (sfp->id.ext.diagmon & (SFP_DIAGMON_DDM | SFP_DIAGMON_ADDRMODE)) !=
	    SFP_DIAGMON_DDM) {
		/* The module appears not to implement bus address 0xa2,
		 * or requires an address change sequence, so assume that
		 * the module powers up in the indicated power mode.
		 */
		if (power > sfp->max_power_mW) {
			dev_err(sfp->dev,
				"Host does not support %u.%uW modules\n",
				power / 1000, (power / 100) % 10);
			return -EINVAL;
		}
		return 0;
	}

	if (power > sfp->max_power_mW) {
		dev_warn(sfp->dev,
			 "Host does not support %u.%uW modules, module left in power mode 1\n",
			 power / 1000, (power / 100) % 10);
		return 0;
	}

	if (power <= 1000)
		return 0;

	err = sfp_read(sfp, true, SFP_EXT_STATUS, &val, sizeof(val));
	if (err != sizeof(val)) {
		dev_err(sfp->dev, "Failed to read EEPROM: %d\n", err);
		err = -EAGAIN;
		goto err;
	}

	val |= BIT(0);

	err = sfp_write(sfp, true, SFP_EXT_STATUS, &val, sizeof(val));
	if (err != sizeof(val)) {
		dev_err(sfp->dev, "Failed to write EEPROM: %d\n", err);
		err = -EAGAIN;
		goto err;
	}

	dev_info(sfp->dev, "Module switched to %u.%uW power level\n",
		 power / 1000, (power / 100) % 10);
	return T_HPOWER_LEVEL;

err:
	return err;
}