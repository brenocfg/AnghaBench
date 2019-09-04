#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int driver_register (int /*<<< orphan*/ *) ; 
 int drvregistered ; 
 TYPE_1__ ipmidriver ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ipmi_register_driver(void)
{
	int rv;

	if (drvregistered)
		return 0;

	rv = driver_register(&ipmidriver.driver);
	if (rv)
		pr_err("Could not register IPMI driver\n");
	else
		drvregistered = true;
	return rv;
}