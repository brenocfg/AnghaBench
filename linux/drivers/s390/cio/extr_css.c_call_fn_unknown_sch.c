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
struct subchannel_id {int dummy; } ;
struct cb_data {int (* fn_unknown_sch ) (struct subchannel_id,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; int /*<<< orphan*/  set; } ;

/* Variables and functions */
 scalar_t__ idset_sch_contains (int /*<<< orphan*/ ,struct subchannel_id) ; 
 int stub1 (struct subchannel_id,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int call_fn_unknown_sch(struct subchannel_id schid, void *data)
{
	struct cb_data *cb = data;
	int rc = 0;

	if (idset_sch_contains(cb->set, schid))
		rc = cb->fn_unknown_sch(schid, cb->data);
	return rc;
}