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
struct cami2c {struct cami2c* ioarea; int /*<<< orphan*/  iobase; int /*<<< orphan*/  irq; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cami2c*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cami2c*) ; 
 struct cami2c* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_resource (struct cami2c*) ; 

__attribute__((used)) static int sh7760_i2c_remove(struct platform_device *pdev)
{
	struct cami2c *id = platform_get_drvdata(pdev);

	i2c_del_adapter(&id->adap);
	free_irq(id->irq, id);
	iounmap(id->iobase);
	release_resource(id->ioarea);
	kfree(id->ioarea);
	kfree(id);

	return 0;
}