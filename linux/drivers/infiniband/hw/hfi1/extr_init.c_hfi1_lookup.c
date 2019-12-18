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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_dev_table ; 
 struct hfi1_devdata* xa_load (int /*<<< orphan*/ *,int) ; 

struct hfi1_devdata *hfi1_lookup(int unit)
{
	return xa_load(&hfi1_dev_table, unit);
}