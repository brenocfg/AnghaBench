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
struct most_channel {int dummy; } ;
struct core_component {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct most_channel* get_channel (char*,char*) ; 
 int link_channel_to_component (struct most_channel*,struct core_component*,char*,char*) ; 
 struct core_component* match_component (char*) ; 

int most_add_link(char *mdev, char *mdev_ch, char *comp_name, char *link_name,
		  char *comp_param)
{
	struct most_channel *c = get_channel(mdev, mdev_ch);
	struct core_component *comp = match_component(comp_name);

	if (!c || !comp)
		return -ENODEV;

	return link_channel_to_component(c, comp, link_name, comp_param);
}