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
struct hv_24x7_event_data {int /*<<< orphan*/  event_group_record_offs; int /*<<< orphan*/  event_counter_offs; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HV_PERF_DOMAIN_PHYS_CHIP 129 
#define  HV_PERF_DOMAIN_PHYS_CORE 128 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*,scalar_t__,char const*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static char *event_fmt(struct hv_24x7_event_data *event, unsigned domain)
{
	const char *sindex;
	const char *lpar;
	const char *domain_str;
	char buf[8];

	switch (domain) {
	case HV_PERF_DOMAIN_PHYS_CHIP:
		snprintf(buf, sizeof(buf), "%d", domain);
		domain_str = buf;
		lpar = "0x0";
		sindex = "chip";
		break;
	case HV_PERF_DOMAIN_PHYS_CORE:
		domain_str = "?";
		lpar = "0x0";
		sindex = "core";
		break;
	default:
		domain_str = "?";
		lpar = "?";
		sindex = "vcpu";
	}

	return kasprintf(GFP_KERNEL,
			"domain=%s,offset=0x%x,%s=?,lpar=%s",
			domain_str,
			be16_to_cpu(event->event_counter_offs) +
				be16_to_cpu(event->event_group_record_offs),
			sindex,
			lpar);
}