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
struct intel_soc_pmic {int /*<<< orphan*/  irq; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct intel_soc_pmic* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static void cht_wc_shutdown(struct i2c_client *client)
{
	struct intel_soc_pmic *pmic = i2c_get_clientdata(client);

	disable_irq(pmic->irq);
}