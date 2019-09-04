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
struct mthca_icm {int dummy; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MAP_ICM_AUX ; 
 int mthca_map_cmd (struct mthca_dev*,int /*<<< orphan*/ ,struct mthca_icm*,int) ; 

int mthca_MAP_ICM_AUX(struct mthca_dev *dev, struct mthca_icm *icm)
{
	return mthca_map_cmd(dev, CMD_MAP_ICM_AUX, icm, -1);
}