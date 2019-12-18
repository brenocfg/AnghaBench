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
struct watchdog_device {int dummy; } ;
struct ltq_wdt_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_WDT_CR ; 
 int LTQ_WDT_CR_GEN ; 
 int /*<<< orphan*/  LTQ_WDT_CR_PW1 ; 
 int /*<<< orphan*/  LTQ_WDT_CR_PW2 ; 
 int LTQ_WDT_CR_PW_MASK ; 
 struct ltq_wdt_priv* ltq_wdt_get_priv (struct watchdog_device*) ; 
 int /*<<< orphan*/  ltq_wdt_mask (struct ltq_wdt_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltq_wdt_stop(struct watchdog_device *wdt)
{
	struct ltq_wdt_priv *priv = ltq_wdt_get_priv(wdt);

	ltq_wdt_mask(priv, LTQ_WDT_CR_PW_MASK, LTQ_WDT_CR_PW1, LTQ_WDT_CR);
	ltq_wdt_mask(priv, LTQ_WDT_CR_GEN | LTQ_WDT_CR_PW_MASK,
		     LTQ_WDT_CR_PW2, LTQ_WDT_CR);

	return 0;
}