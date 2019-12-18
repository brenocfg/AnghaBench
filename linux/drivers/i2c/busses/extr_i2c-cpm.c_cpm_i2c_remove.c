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
struct cpm_i2c {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpm_i2c_shutdown (struct cpm_i2c*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cpm_i2c*) ; 
 struct cpm_i2c* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cpm_i2c_remove(struct platform_device *ofdev)
{
	struct cpm_i2c *cpm = platform_get_drvdata(ofdev);

	i2c_del_adapter(&cpm->adap);

	cpm_i2c_shutdown(cpm);

	kfree(cpm);

	return 0;
}