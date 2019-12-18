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
struct etr_buf {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* alloc ) (struct tmc_drvdata*,struct etr_buf*,int,void**) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  ETR_MODE_CATU 130 
#define  ETR_MODE_ETR_SG 129 
#define  ETR_MODE_FLAT 128 
 TYPE_1__** etr_buf_ops ; 
 int stub1 (struct tmc_drvdata*,struct etr_buf*,int,void**) ; 

__attribute__((used)) static inline int tmc_etr_mode_alloc_buf(int mode,
					 struct tmc_drvdata *drvdata,
					 struct etr_buf *etr_buf, int node,
					 void **pages)
{
	int rc = -EINVAL;

	switch (mode) {
	case ETR_MODE_FLAT:
	case ETR_MODE_ETR_SG:
	case ETR_MODE_CATU:
		if (etr_buf_ops[mode] && etr_buf_ops[mode]->alloc)
			rc = etr_buf_ops[mode]->alloc(drvdata, etr_buf,
						      node, pages);
		if (!rc)
			etr_buf->ops = etr_buf_ops[mode];
		return rc;
	default:
		return -EINVAL;
	}
}