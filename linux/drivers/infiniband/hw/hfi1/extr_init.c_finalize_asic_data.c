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
struct hfi1_devdata {int dummy; } ;
struct hfi1_asic_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_up_i2c (struct hfi1_devdata*,struct hfi1_asic_data*) ; 
 int /*<<< orphan*/  kfree (struct hfi1_asic_data*) ; 

__attribute__((used)) static void finalize_asic_data(struct hfi1_devdata *dd,
			       struct hfi1_asic_data *ad)
{
	clean_up_i2c(dd, ad);
	kfree(ad);
}