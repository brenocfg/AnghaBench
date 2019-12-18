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
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct rwdt_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ MUL_BY_CLKS_PER_SEC (struct rwdt_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RWTCNT ; 
 int /*<<< orphan*/  rwdt_write (struct rwdt_priv*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rwdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int rwdt_init_timeout(struct watchdog_device *wdev)
{
	struct rwdt_priv *priv = watchdog_get_drvdata(wdev);

	rwdt_write(priv, 65536 - MUL_BY_CLKS_PER_SEC(priv, wdev->timeout), RWTCNT);

	return 0;
}