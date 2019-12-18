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
struct watchdog_device {int /*<<< orphan*/  status; } ;
struct esb_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESB_LOCK_REG ; 
 int /*<<< orphan*/  ESB_RELOAD_REG (struct esb_dev*) ; 
 int ESB_WDT_ENABLE ; 
 int ESB_WDT_LOCK ; 
 int /*<<< orphan*/  ESB_WDT_RELOAD ; 
 int /*<<< orphan*/  WDOG_NO_WAY_OUT ; 
 int /*<<< orphan*/  esb_unlock_registers (struct esb_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct esb_dev* to_esb_dev (struct watchdog_device*) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esb_timer_start(struct watchdog_device *wdd)
{
	struct esb_dev *edev = to_esb_dev(wdd);
	int _wdd_nowayout = test_bit(WDOG_NO_WAY_OUT, &wdd->status);
	u8 val;

	esb_unlock_registers(edev);
	writew(ESB_WDT_RELOAD, ESB_RELOAD_REG(edev));
	/* Enable or Enable + Lock? */
	val = ESB_WDT_ENABLE | (_wdd_nowayout ? ESB_WDT_LOCK : 0x00);
	pci_write_config_byte(edev->pdev, ESB_LOCK_REG, val);
	return 0;
}