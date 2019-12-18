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
struct cxl {int /*<<< orphan*/  adapter_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_adapter_idr ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cxl_remove_adapter_nr(struct cxl *adapter)
{
	idr_remove(&cxl_adapter_idr, adapter->adapter_num);
}