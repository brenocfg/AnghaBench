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
struct hv_24x7_event_data {int dummy; } ;
struct attribute {int dummy; } ;

/* Variables and functions */
 struct attribute* device_str_attr_create (char*,int,int,char*,int) ; 
 char* event_desc (struct hv_24x7_event_data*,int*) ; 
 char* event_name (struct hv_24x7_event_data*,int*) ; 

__attribute__((used)) static struct attribute *event_to_desc_attr(struct hv_24x7_event_data *event,
					    int nonce)
{
	int nl, dl;
	char *name = event_name(event, &nl);
	char *desc = event_desc(event, &dl);

	/* If there isn't a description, don't create the sysfs file */
	if (!dl)
		return NULL;

	return device_str_attr_create(name, nl, nonce, desc, dl);
}