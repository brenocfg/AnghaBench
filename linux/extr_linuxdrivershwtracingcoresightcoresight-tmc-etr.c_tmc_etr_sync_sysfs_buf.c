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
struct tmc_drvdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tmc_sync_etr_buf (struct tmc_drvdata*) ; 

__attribute__((used)) static void tmc_etr_sync_sysfs_buf(struct tmc_drvdata *drvdata)
{
	tmc_sync_etr_buf(drvdata);
}