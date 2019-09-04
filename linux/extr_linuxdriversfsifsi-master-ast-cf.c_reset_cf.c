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
struct fsi_master_acf {int /*<<< orphan*/  scu; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_COPRO_CTRL ; 
 int /*<<< orphan*/  SCU_COPRO_RESET ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void reset_cf(struct fsi_master_acf *master)
{
	regmap_write(master->scu, SCU_COPRO_CTRL, SCU_COPRO_RESET);
	usleep_range(20,20);
	regmap_write(master->scu, SCU_COPRO_CTRL, 0);
	usleep_range(20,20);
}