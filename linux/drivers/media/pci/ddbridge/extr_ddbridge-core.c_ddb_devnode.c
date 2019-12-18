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
typedef  int /*<<< orphan*/  umode_t ;
struct device {int dummy; } ;
struct ddb {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ddb* dev_get_drvdata (struct device*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ddb_devnode(struct device *device, umode_t *mode)
{
	struct ddb *dev = dev_get_drvdata(device);

	return kasprintf(GFP_KERNEL, "ddbridge/card%d", dev->nr);
}