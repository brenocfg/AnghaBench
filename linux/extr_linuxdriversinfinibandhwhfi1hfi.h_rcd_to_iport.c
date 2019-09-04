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
struct hfi1_ibport {int dummy; } ;
struct hfi1_ctxtdata {TYPE_1__* ppd; } ;
struct TYPE_2__ {struct hfi1_ibport ibport_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct hfi1_ibport *rcd_to_iport(struct hfi1_ctxtdata *rcd)
{
	return &rcd->ppd->ibport_data;
}