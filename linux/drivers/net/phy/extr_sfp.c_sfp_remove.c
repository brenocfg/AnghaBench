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
struct sfp {int /*<<< orphan*/  sfp_bus; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct sfp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sfp_unregister_socket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sfp_remove(struct platform_device *pdev)
{
	struct sfp *sfp = platform_get_drvdata(pdev);

	sfp_unregister_socket(sfp->sfp_bus);

	return 0;
}