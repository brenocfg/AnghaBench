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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7610E_FIRMWARE ; 
 int /*<<< orphan*/  MT7610U_FIRMWARE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int firmware_request_nowarn (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt76x0_get_firmware(struct mt76x02_dev *dev,
			       const struct firmware **fw)
{
	int err;

	/* try to load mt7610e fw if available
	 * otherwise fall back to mt7610u one
	 */
	err = firmware_request_nowarn(fw, MT7610E_FIRMWARE, dev->mt76.dev);
	if (err) {
		dev_info(dev->mt76.dev, "%s not found, switching to %s",
			 MT7610E_FIRMWARE, MT7610U_FIRMWARE);
		return request_firmware(fw, MT7610U_FIRMWARE,
					dev->mt76.dev);
	}
	return 0;
}