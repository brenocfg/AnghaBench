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
struct tmc_drvdata {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tmc_etb_disable_hw (struct tmc_drvdata*) ; 
 int /*<<< orphan*/  coresight_disclaim_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tmc_etb_disable_hw(struct tmc_drvdata *drvdata)
{
	__tmc_etb_disable_hw(drvdata);
	coresight_disclaim_device(drvdata->base);
}