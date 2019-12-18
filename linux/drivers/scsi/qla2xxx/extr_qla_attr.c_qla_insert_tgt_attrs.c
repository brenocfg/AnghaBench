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
struct device_attribute {int dummy; } ;

/* Variables and functions */
 struct device_attribute dev_attr_ql2xexchoffld ; 
 struct device_attribute dev_attr_ql2xiniexchg ; 
 struct device_attribute dev_attr_qlini_mode ; 
 struct device_attribute** qla2x00_host_attrs ; 

void qla_insert_tgt_attrs(void)
{
	struct device_attribute **attr;

	/* advance to empty slot */
	for (attr = &qla2x00_host_attrs[0]; *attr; ++attr)
		continue;

	*attr = &dev_attr_qlini_mode;
	attr++;
	*attr = &dev_attr_ql2xiniexchg;
	attr++;
	*attr = &dev_attr_ql2xexchoffld;
}