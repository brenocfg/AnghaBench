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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ds1307 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1307_TRICKLE_CHARGER_250_OHM ; 
 int /*<<< orphan*/  DS1307_TRICKLE_CHARGER_2K_OHM ; 
 int /*<<< orphan*/  DS1307_TRICKLE_CHARGER_4K_OHM ; 
 int /*<<< orphan*/  DS1307_TRICKLE_CHARGER_DIODE ; 
 int /*<<< orphan*/  DS1307_TRICKLE_CHARGER_NO_DIODE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static u8 do_trickle_setup_ds1339(struct ds1307 *ds1307, u32 ohms, bool diode)
{
	u8 setup = (diode) ? DS1307_TRICKLE_CHARGER_DIODE :
		DS1307_TRICKLE_CHARGER_NO_DIODE;

	switch (ohms) {
	case 250:
		setup |= DS1307_TRICKLE_CHARGER_250_OHM;
		break;
	case 2000:
		setup |= DS1307_TRICKLE_CHARGER_2K_OHM;
		break;
	case 4000:
		setup |= DS1307_TRICKLE_CHARGER_4K_OHM;
		break;
	default:
		dev_warn(ds1307->dev,
			 "Unsupported ohm value %u in dt\n", ohms);
		return 0;
	}
	return setup;
}