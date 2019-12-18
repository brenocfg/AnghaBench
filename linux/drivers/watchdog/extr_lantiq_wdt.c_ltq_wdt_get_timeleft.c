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
typedef  int u64 ;
struct watchdog_device {int dummy; } ;
struct ltq_wdt_priv {int /*<<< orphan*/  clk_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_WDT_SR ; 
 int LTQ_WDT_SR_VALUE_MASK ; 
 unsigned int do_div (int,int /*<<< orphan*/ ) ; 
 struct ltq_wdt_priv* ltq_wdt_get_priv (struct watchdog_device*) ; 
 int ltq_wdt_r32 (struct ltq_wdt_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ltq_wdt_get_timeleft(struct watchdog_device *wdt)
{
	struct ltq_wdt_priv *priv = ltq_wdt_get_priv(wdt);
	u64 timeout;

	timeout = ltq_wdt_r32(priv, LTQ_WDT_SR) & LTQ_WDT_SR_VALUE_MASK;
	return do_div(timeout, priv->clk_rate);
}