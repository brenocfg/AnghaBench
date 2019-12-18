#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct send_context_info {scalar_t__ type; struct send_context* sc; } ;
struct send_context {int dummy; } ;
struct hfi1_devdata {TYPE_1__* vld; struct send_context_info* send_contexts; } ;
struct TYPE_2__ {struct send_context* sc; } ;

/* Variables and functions */
 scalar_t__ SC_KERNEL ; 
 scalar_t__ SC_VL15 ; 
 int num_vls ; 

__attribute__((used)) static int sc_to_vl(struct hfi1_devdata *dd, int sw_index)
{
	struct send_context_info *sci;
	struct send_context *sc;
	int i;

	sci = &dd->send_contexts[sw_index];

	/* there is no information for user (PSM) and ack contexts */
	if ((sci->type != SC_KERNEL) && (sci->type != SC_VL15))
		return -1;

	sc = sci->sc;
	if (!sc)
		return -1;
	if (dd->vld[15].sc == sc)
		return 15;
	for (i = 0; i < num_vls; i++)
		if (dd->vld[i].sc == sc)
			return i;

	return -1;
}