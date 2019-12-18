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
struct watchdog_device {int timeout; } ;
struct ltq_wdt_priv {int clk_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_WDT_CR ; 
 int LTQ_WDT_CR_MAX_TIMEOUT ; 
 int LTQ_WDT_CR_PW1 ; 
 int LTQ_WDT_CR_PW2 ; 
 int LTQ_WDT_CR_PW_MASK ; 
 struct ltq_wdt_priv* ltq_wdt_get_priv (struct watchdog_device*) ; 
 int /*<<< orphan*/  ltq_wdt_mask (struct ltq_wdt_priv*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltq_wdt_ping(struct watchdog_device *wdt)
{
	struct ltq_wdt_priv *priv = ltq_wdt_get_priv(wdt);
	u32 timeout;

	timeout = wdt->timeout * priv->clk_rate;

	ltq_wdt_mask(priv, LTQ_WDT_CR_PW_MASK, LTQ_WDT_CR_PW1, LTQ_WDT_CR);
	/* write the second magic plus the configuration and new timeout */
	ltq_wdt_mask(priv, LTQ_WDT_CR_PW_MASK | LTQ_WDT_CR_MAX_TIMEOUT,
		     LTQ_WDT_CR_PW2 | timeout, LTQ_WDT_CR);

	return 0;
}