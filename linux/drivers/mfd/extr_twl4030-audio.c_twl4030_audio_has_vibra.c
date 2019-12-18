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
struct twl4030_audio_data {scalar_t__ vibra; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static bool twl4030_audio_has_vibra(struct twl4030_audio_data *pdata,
			      struct device_node *node)
{
	int vibra;

	if (pdata && pdata->vibra)
		return true;

	if (!of_property_read_u32(node, "ti,enable-vibra", &vibra) && vibra)
		return true;

	return false;
}