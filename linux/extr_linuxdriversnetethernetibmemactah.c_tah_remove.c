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
struct tah_instance {scalar_t__ users; int /*<<< orphan*/  base; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tah_instance*) ; 
 struct tah_instance* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tah_remove(struct platform_device *ofdev)
{
	struct tah_instance *dev = platform_get_drvdata(ofdev);

	WARN_ON(dev->users != 0);

	iounmap(dev->base);
	kfree(dev);

	return 0;
}