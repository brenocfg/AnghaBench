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

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmobile_reset_nb ; 
 int /*<<< orphan*/  sysc_base2 ; 
 int /*<<< orphan*/  unregister_restart_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rmobile_reset_remove(struct platform_device *pdev)
{
	unregister_restart_handler(&rmobile_reset_nb);
	iounmap(sysc_base2);
	return 0;
}