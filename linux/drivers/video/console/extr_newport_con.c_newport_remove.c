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
struct gio_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  give_up_console (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  newport_con ; 
 scalar_t__ npregs ; 

__attribute__((used)) static void newport_remove(struct gio_device *dev)
{
	give_up_console(&newport_con);
	iounmap((void *)npregs);
}