#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tpiu_drvdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct tpiu_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpiu_disable_hw (struct tpiu_drvdata*) ; 

__attribute__((used)) static int tpiu_disable(struct coresight_device *csdev)
{
	struct tpiu_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	if (atomic_dec_return(csdev->refcnt))
		return -EBUSY;

	tpiu_disable_hw(drvdata);

	dev_dbg(&csdev->dev, "TPIU disabled\n");
	return 0;
}