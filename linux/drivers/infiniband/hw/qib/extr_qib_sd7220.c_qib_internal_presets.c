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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ DDS_3M ; 
 scalar_t__ dds_init_vals ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int qib_rxeq_set ; 
 int set_dds_vals (struct qib_devdata*,scalar_t__) ; 
 int set_rxeq_vals (struct qib_devdata*,int) ; 

__attribute__((used)) static int qib_internal_presets(struct qib_devdata *dd)
{
	int ret = 0;

	ret = set_dds_vals(dd, dds_init_vals + DDS_3M);

	if (ret < 0)
		qib_dev_err(dd, "Failed to set default DDS values\n");
	ret = set_rxeq_vals(dd, qib_rxeq_set & 3);
	if (ret < 0)
		qib_dev_err(dd, "Failed to set default RXEQ values\n");
	return ret;
}