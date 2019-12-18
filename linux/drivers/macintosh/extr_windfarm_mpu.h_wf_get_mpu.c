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
typedef  void mpu_data ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_path (char*) ; 
 void* of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static inline const struct mpu_data *wf_get_mpu(int cpu)
{
	struct device_node *np;
	char nodename[64];
	const void *data;
	int len;

	/*
	 * prom.c routine for finding a node by path is a bit brain dead
	 * and requires exact @xxx unit numbers. This is a bit ugly but
	 * will work for these machines
	 */
	sprintf(nodename, "/u3@0,f8000000/i2c@f8001000/cpuid@a%d", cpu ? 2 : 0);
	np = of_find_node_by_path(nodename);
	if (!np)
		return NULL;
	data = of_get_property(np, "cpuid", &len);	
	of_node_put(np);
	if (!data)
		return NULL;

	/*
	 * We are naughty, we have dropped the reference to the device
	 * node and still return a pointer to the content. We know we
	 * can do that though as this is only ever called on PowerMac
	 * which cannot remove those nodes
	 */
	return data;
}