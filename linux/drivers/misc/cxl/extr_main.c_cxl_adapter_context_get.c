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
struct cxl {int /*<<< orphan*/  contexts_num; } ;

/* Variables and functions */
 int EBUSY ; 
 int atomic_inc_unless_negative (int /*<<< orphan*/ *) ; 

int cxl_adapter_context_get(struct cxl *adapter)
{
	int rc;

	rc = atomic_inc_unless_negative(&adapter->contexts_num);
	return rc ? 0 : -EBUSY;
}