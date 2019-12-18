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
struct platform_device {int dummy; } ;
struct cht_wc_i2c_adap {int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  adapter; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 struct cht_wc_i2c_adap* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cht_wc_i2c_adap_i2c_remove(struct platform_device *pdev)
{
	struct cht_wc_i2c_adap *adap = platform_get_drvdata(pdev);

	i2c_unregister_device(adap->client);
	i2c_del_adapter(&adap->adapter);
	irq_domain_remove(adap->irq_domain);

	return 0;
}