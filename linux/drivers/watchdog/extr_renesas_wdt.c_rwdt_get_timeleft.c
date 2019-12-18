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
typedef  scalar_t__ u16 ;
struct watchdog_device {int dummy; } ;
struct rwdt_priv {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int DIV_BY_CLKS_PER_SEC (struct rwdt_priv*,scalar_t__) ; 
 scalar_t__ RWTCNT ; 
 scalar_t__ readw_relaxed (scalar_t__) ; 
 struct rwdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int rwdt_get_timeleft(struct watchdog_device *wdev)
{
	struct rwdt_priv *priv = watchdog_get_drvdata(wdev);
	u16 val = readw_relaxed(priv->base + RWTCNT);

	return DIV_BY_CLKS_PER_SEC(priv, 65536 - val);
}