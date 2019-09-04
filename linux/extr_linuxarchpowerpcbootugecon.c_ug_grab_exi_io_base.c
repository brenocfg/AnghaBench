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
typedef  int /*<<< orphan*/  v ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 void* find_node_by_compatible (int /*<<< orphan*/ *,char*) ; 
 int getprop (void*,char*,scalar_t__*,int) ; 

__attribute__((used)) static void *ug_grab_exi_io_base(void)
{
	u32 v;
	void *devp;

	devp = find_node_by_compatible(NULL, "nintendo,flipper-exi");
	if (devp == NULL)
		goto err_out;
	if (getprop(devp, "virtual-reg", &v, sizeof(v)) != sizeof(v))
		goto err_out;

	return (void *)v;

err_out:
	return NULL;
}