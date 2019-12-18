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
struct pcan_pccard {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 int pcan_write_eeprom (struct pcan_pccard*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void pcan_set_can_power(struct pcan_pccard *card, int onoff)
{
	int err;

	err = pcan_write_eeprom(card, 0, !!onoff);
	if (err)
		dev_err(&card->pdev->dev,
			"failed setting power %s to can connectors (err %d)\n",
			(onoff) ? "on" : "off", err);
}