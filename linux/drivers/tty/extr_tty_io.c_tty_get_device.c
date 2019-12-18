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
struct tty_struct {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 struct device* class_find_device_by_devt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_class ; 
 int /*<<< orphan*/  tty_devnum (struct tty_struct*) ; 

__attribute__((used)) static struct device *tty_get_device(struct tty_struct *tty)
{
	dev_t devt = tty_devnum(tty);
	return class_find_device_by_devt(tty_class, devt);
}