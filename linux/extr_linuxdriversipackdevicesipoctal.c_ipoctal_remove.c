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
struct ipack_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipoctal_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoctal_remove(struct ipack_device *idev)
{
	__ipoctal_remove(dev_get_drvdata(&idev->dev));
}