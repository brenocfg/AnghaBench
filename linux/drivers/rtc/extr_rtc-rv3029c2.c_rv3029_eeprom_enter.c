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
typedef  int u8 ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RV3029_ONOFF_CTRL ; 
 int /*<<< orphan*/  RV3029_ONOFF_CTRL_EERE ; 
 int RV3029_STATUS_VLOW1 ; 
 int RV3029_STATUS_VLOW2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int rv3029_eeprom_busywait (struct device*) ; 
 int /*<<< orphan*/  rv3029_eeprom_exit (struct device*) ; 
 int rv3029_get_sr (struct device*,int*) ; 
 int rv3029_set_sr (struct device*,int) ; 
 int rv3029_update_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rv3029_eeprom_enter(struct device *dev)
{
	int ret;
	u8 sr;

	/* Check whether we are in the allowed voltage range. */
	ret = rv3029_get_sr(dev, &sr);
	if (ret < 0)
		return ret;
	if (sr & (RV3029_STATUS_VLOW1 | RV3029_STATUS_VLOW2)) {
		/* We clear the bits and retry once just in case
		 * we had a brown out in early startup.
		 */
		sr &= ~RV3029_STATUS_VLOW1;
		sr &= ~RV3029_STATUS_VLOW2;
		ret = rv3029_set_sr(dev, sr);
		if (ret < 0)
			return ret;
		usleep_range(1000, 10000);
		ret = rv3029_get_sr(dev, &sr);
		if (ret < 0)
			return ret;
		if (sr & (RV3029_STATUS_VLOW1 | RV3029_STATUS_VLOW2)) {
			dev_err(dev,
				"Supply voltage is too low to safely access the EEPROM.\n");
			return -ENODEV;
		}
	}

	/* Disable eeprom refresh. */
	ret = rv3029_update_bits(dev, RV3029_ONOFF_CTRL, RV3029_ONOFF_CTRL_EERE,
				 0);
	if (ret < 0)
		return ret;

	/* Wait for any previous eeprom accesses to finish. */
	ret = rv3029_eeprom_busywait(dev);
	if (ret < 0)
		rv3029_eeprom_exit(dev);

	return ret;
}