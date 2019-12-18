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
typedef  int u8 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
#define  nvme_fabrics_type_connect 130 
#define  nvme_fabrics_type_property_get 129 
#define  nvme_fabrics_type_property_set 128 
 char const* nvme_trace_fabrics_common (struct trace_seq*,int*) ; 
 char const* nvme_trace_fabrics_connect (struct trace_seq*,int*) ; 
 char const* nvme_trace_fabrics_property_get (struct trace_seq*,int*) ; 
 char const* nvme_trace_fabrics_property_set (struct trace_seq*,int*) ; 

const char *nvme_trace_parse_fabrics_cmd(struct trace_seq *p,
		u8 fctype, u8 *spc)
{
	switch (fctype) {
	case nvme_fabrics_type_property_set:
		return nvme_trace_fabrics_property_set(p, spc);
	case nvme_fabrics_type_connect:
		return nvme_trace_fabrics_connect(p, spc);
	case nvme_fabrics_type_property_get:
		return nvme_trace_fabrics_property_get(p, spc);
	default:
		return nvme_trace_fabrics_common(p, spc);
	}
}