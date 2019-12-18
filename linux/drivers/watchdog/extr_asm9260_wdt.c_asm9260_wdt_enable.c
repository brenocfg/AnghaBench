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
struct watchdog_device {int dummy; } ;
struct asm9260_wdt_priv {scalar_t__ mode; scalar_t__ iobase; } ;

/* Variables and functions */
 int BM_MOD_WDEN ; 
 int BM_MOD_WDRESET ; 
 scalar_t__ HW_RESET ; 
 scalar_t__ HW_WDMOD ; 
 int /*<<< orphan*/  asm9260_wdt_feed (struct watchdog_device*) ; 
 int /*<<< orphan*/  asm9260_wdt_updatetimeout (struct watchdog_device*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct asm9260_wdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int asm9260_wdt_enable(struct watchdog_device *wdd)
{
	struct asm9260_wdt_priv *priv = watchdog_get_drvdata(wdd);
	u32 mode = 0;

	if (priv->mode == HW_RESET)
		mode = BM_MOD_WDRESET;

	iowrite32(BM_MOD_WDEN | mode, priv->iobase + HW_WDMOD);

	asm9260_wdt_updatetimeout(wdd);

	asm9260_wdt_feed(wdd);

	return 0;
}