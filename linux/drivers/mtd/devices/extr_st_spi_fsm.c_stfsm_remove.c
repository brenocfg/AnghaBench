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
struct stfsm {int /*<<< orphan*/  mtd; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct stfsm* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int stfsm_remove(struct platform_device *pdev)
{
	struct stfsm *fsm = platform_get_drvdata(pdev);

	return mtd_device_unregister(&fsm->mtd);
}