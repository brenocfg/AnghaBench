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
struct riowd {int /*<<< orphan*/  regs; } ;
struct platform_device {int /*<<< orphan*/ * resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct riowd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  riowd_miscdev ; 

__attribute__((used)) static int riowd_remove(struct platform_device *op)
{
	struct riowd *p = platform_get_drvdata(op);

	misc_deregister(&riowd_miscdev);
	of_iounmap(&op->resource[0], p->regs, 2);

	return 0;
}