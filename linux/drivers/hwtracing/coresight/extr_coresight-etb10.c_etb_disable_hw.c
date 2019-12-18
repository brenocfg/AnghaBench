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
struct etb_drvdata {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __etb_disable_hw (struct etb_drvdata*) ; 
 int /*<<< orphan*/  coresight_disclaim_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etb_dump_hw (struct etb_drvdata*) ; 

__attribute__((used)) static void etb_disable_hw(struct etb_drvdata *drvdata)
{
	__etb_disable_hw(drvdata);
	etb_dump_hw(drvdata);
	coresight_disclaim_device(drvdata->base);
}