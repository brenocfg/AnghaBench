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
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_coredumpm (struct device*,int /*<<< orphan*/ *,struct scatterlist*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devcd_free_sgtable ; 
 int /*<<< orphan*/  devcd_read_from_sgtable ; 

void dev_coredumpsg(struct device *dev, struct scatterlist *table,
		    size_t datalen, gfp_t gfp)
{
	dev_coredumpm(dev, NULL, table, datalen, gfp, devcd_read_from_sgtable,
		      devcd_free_sgtable);
}