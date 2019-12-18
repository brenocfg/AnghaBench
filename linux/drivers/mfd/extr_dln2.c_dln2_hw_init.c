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
struct dln2_dev {int dummy; } ;

/* Variables and functions */
 int dln2_check_hw (struct dln2_dev*) ; 
 int dln2_print_serialno (struct dln2_dev*) ; 

__attribute__((used)) static int dln2_hw_init(struct dln2_dev *dln2)
{
	int ret;

	ret = dln2_check_hw(dln2);
	if (ret < 0)
		return ret;

	return dln2_print_serialno(dln2);
}