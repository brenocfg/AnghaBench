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
typedef  union ib_flow_spec {int dummy; } ib_flow_spec ;
struct ib_uverbs_flow_spec_hdr {int dummy; } ;
struct ib_uverbs_flow_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  hdr; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ib_uverbs_kern_spec_to_ib_spec_filter (int /*<<< orphan*/ ,void*,void*,int,union ib_flow_spec*) ; 
 int kern_spec_filter_sz (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kern_spec_to_ib_spec_filter(struct ib_uverbs_flow_spec *kern_spec,
				       union ib_flow_spec *ib_spec)
{
	ssize_t kern_filter_sz;
	void *kern_spec_mask;
	void *kern_spec_val;

	kern_filter_sz = kern_spec_filter_sz(&kern_spec->hdr);

	kern_spec_val = (void *)kern_spec +
		sizeof(struct ib_uverbs_flow_spec_hdr);
	kern_spec_mask = kern_spec_val + kern_filter_sz;

	return ib_uverbs_kern_spec_to_ib_spec_filter(kern_spec->type,
						     kern_spec_mask,
						     kern_spec_val,
						     kern_filter_sz, ib_spec);
}