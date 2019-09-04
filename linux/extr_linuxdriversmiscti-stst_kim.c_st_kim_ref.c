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
struct st_data_s {int dummy; } ;
struct platform_device {int dummy; } ;
struct kim_data_s {struct st_data_s* core_data; } ;

/* Variables and functions */
 struct kim_data_s* platform_get_drvdata (struct platform_device*) ; 
 struct platform_device* st_get_plat_device (int) ; 

void st_kim_ref(struct st_data_s **core_data, int id)
{
	struct platform_device	*pdev;
	struct kim_data_s	*kim_gdata;
	/* get kim_gdata reference from platform device */
	pdev = st_get_plat_device(id);
	if (!pdev)
		goto err;
	kim_gdata = platform_get_drvdata(pdev);
	if (!kim_gdata)
		goto err;

	*core_data = kim_gdata->core_data;
	return;
err:
	*core_data = NULL;
}