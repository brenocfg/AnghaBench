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
struct platform_device {int dummy; } ;
struct platform_data {scalar_t__* core_data; } ;

/* Variables and functions */
 int MAX_CORE_DATA ; 
 int /*<<< orphan*/  coretemp_remove_core (struct platform_data*,int) ; 
 struct platform_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int coretemp_remove(struct platform_device *pdev)
{
	struct platform_data *pdata = platform_get_drvdata(pdev);
	int i;

	for (i = MAX_CORE_DATA - 1; i >= 0; --i)
		if (pdata->core_data[i])
			coretemp_remove_core(pdata, i);

	return 0;
}