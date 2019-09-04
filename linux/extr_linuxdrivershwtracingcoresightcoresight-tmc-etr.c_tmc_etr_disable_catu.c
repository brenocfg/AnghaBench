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
struct tmc_drvdata {int /*<<< orphan*/  etr_buf; } ;
struct coresight_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct coresight_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* helper_ops (struct coresight_device*) ; 
 int /*<<< orphan*/  stub1 (struct coresight_device*,int /*<<< orphan*/ ) ; 
 struct coresight_device* tmc_etr_get_catu_device (struct tmc_drvdata*) ; 

__attribute__((used)) static inline void tmc_etr_disable_catu(struct tmc_drvdata *drvdata)
{
	struct coresight_device *catu = tmc_etr_get_catu_device(drvdata);

	if (catu && helper_ops(catu)->disable)
		helper_ops(catu)->disable(catu, drvdata->etr_buf);
}