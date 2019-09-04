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
struct cyttsp_tch {int dummy; } ;
struct cyttsp_xydata {struct cyttsp_tch const tch4; struct cyttsp_tch const tch3; struct cyttsp_tch const tch2; struct cyttsp_tch const tch1; } ;

/* Variables and functions */

__attribute__((used)) static const struct cyttsp_tch *cyttsp_get_tch(struct cyttsp_xydata *xy_data,
					       int idx)
{
	switch (idx) {
	case 0:
		return &xy_data->tch1;
	case 1:
		return &xy_data->tch2;
	case 2:
		return &xy_data->tch3;
	case 3:
		return &xy_data->tch4;
	default:
		return NULL;
	}
}