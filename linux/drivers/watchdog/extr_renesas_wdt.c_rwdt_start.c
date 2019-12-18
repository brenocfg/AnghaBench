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
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct rwdt_priv {int cks; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ RWTCSRA ; 
 int RWTCSRA_TME ; 
 int RWTCSRA_WRFLG ; 
 scalar_t__ RWTCSRB ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int readb_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  rwdt_init_timeout (struct watchdog_device*) ; 
 int /*<<< orphan*/  rwdt_wait_cycles (struct rwdt_priv*,int) ; 
 int /*<<< orphan*/  rwdt_write (struct rwdt_priv*,int,scalar_t__) ; 
 struct rwdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int rwdt_start(struct watchdog_device *wdev)
{
	struct rwdt_priv *priv = watchdog_get_drvdata(wdev);
	u8 val;

	pm_runtime_get_sync(wdev->parent);

	/* Stop the timer before we modify any register */
	val = readb_relaxed(priv->base + RWTCSRA) & ~RWTCSRA_TME;
	rwdt_write(priv, val, RWTCSRA);
	/* Delay 2 cycles before setting watchdog counter */
	rwdt_wait_cycles(priv, 2);

	rwdt_init_timeout(wdev);
	rwdt_write(priv, priv->cks, RWTCSRA);
	rwdt_write(priv, 0, RWTCSRB);

	while (readb_relaxed(priv->base + RWTCSRA) & RWTCSRA_WRFLG)
		cpu_relax();

	rwdt_write(priv, priv->cks | RWTCSRA_TME, RWTCSRA);

	return 0;
}