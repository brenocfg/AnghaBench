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
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct rwdt_priv {int /*<<< orphan*/  cks; } ;

/* Variables and functions */
 int /*<<< orphan*/  RWTCSRA ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwdt_wait_cycles (struct rwdt_priv*,int) ; 
 int /*<<< orphan*/  rwdt_write (struct rwdt_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rwdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int rwdt_stop(struct watchdog_device *wdev)
{
	struct rwdt_priv *priv = watchdog_get_drvdata(wdev);

	rwdt_write(priv, priv->cks, RWTCSRA);
	/* Delay 3 cycles before disabling module clock */
	rwdt_wait_cycles(priv, 3);
	pm_runtime_put(wdev->parent);

	return 0;
}