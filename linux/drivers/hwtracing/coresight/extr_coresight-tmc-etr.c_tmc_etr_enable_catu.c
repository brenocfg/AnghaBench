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
struct tmc_drvdata {int dummy; } ;
struct etr_buf {int dummy; } ;
struct coresight_device {int dummy; } ;
struct TYPE_2__ {int (* enable ) (struct coresight_device*,struct etr_buf*) ;} ;

/* Variables and functions */
 TYPE_1__* helper_ops (struct coresight_device*) ; 
 int stub1 (struct coresight_device*,struct etr_buf*) ; 
 struct coresight_device* tmc_etr_get_catu_device (struct tmc_drvdata*) ; 

__attribute__((used)) static inline int tmc_etr_enable_catu(struct tmc_drvdata *drvdata,
				      struct etr_buf *etr_buf)
{
	struct coresight_device *catu = tmc_etr_get_catu_device(drvdata);

	if (catu && helper_ops(catu)->enable)
		return helper_ops(catu)->enable(catu, etr_buf);
	return 0;
}