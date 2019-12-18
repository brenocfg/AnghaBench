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
struct ucsi_ccg {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  ucsi; int /*<<< orphan*/  work; int /*<<< orphan*/  pm_work; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ucsi_ccg*) ; 
 struct ucsi_ccg* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucsi_unregister_ppm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucsi_ccg_remove(struct i2c_client *client)
{
	struct ucsi_ccg *uc = i2c_get_clientdata(client);

	cancel_work_sync(&uc->pm_work);
	cancel_work_sync(&uc->work);
	ucsi_unregister_ppm(uc->ucsi);
	pm_runtime_disable(uc->dev);
	free_irq(uc->irq, uc);

	return 0;
}