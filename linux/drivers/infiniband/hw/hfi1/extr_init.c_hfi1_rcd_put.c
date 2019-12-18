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
struct hfi1_ctxtdata {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_rcd_free ; 
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int hfi1_rcd_put(struct hfi1_ctxtdata *rcd)
{
	if (rcd)
		return kref_put(&rcd->kref, hfi1_rcd_free);

	return 0;
}