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
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct attribute* device_str_attr_create_ (char*,char*) ; 
 int /*<<< orphan*/  domain_is_valid (unsigned int) ; 
 char* event_fmt (struct hv_24x7_event_data*,unsigned int) ; 
 char* event_name (struct hv_24x7_event_data*,int*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int,char*,...) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static struct attribute *event_to_attr(unsigned ix,
				       struct hv_24x7_event_data *event,
				       unsigned domain,
				       int nonce)
{
	int event_name_len;
	char *ev_name, *a_ev_name, *val;
	struct attribute *attr;

	if (!domain_is_valid(domain)) {
		pr_warn("catalog event %u has invalid domain %u\n",
				ix, domain);
		return NULL;
	}

	val = event_fmt(event, domain);
	if (!val)
		return NULL;

	ev_name = event_name(event, &event_name_len);
	if (!nonce)
		a_ev_name = kasprintf(GFP_KERNEL, "%.*s",
				(int)event_name_len, ev_name);
	else
		a_ev_name = kasprintf(GFP_KERNEL, "%.*s__%d",
				(int)event_name_len, ev_name, nonce);

	if (!a_ev_name)
		goto out_val;

	attr = device_str_attr_create_(a_ev_name, val);
	if (!attr)
		goto out_name;

	return attr;
out_name:
	kfree(a_ev_name);
out_val:
	kfree(val);
	return NULL;
}