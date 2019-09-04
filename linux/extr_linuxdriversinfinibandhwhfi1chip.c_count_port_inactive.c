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
struct hfi1_devdata {int /*<<< orphan*/  pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  __count_port_discards (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void count_port_inactive(struct hfi1_devdata *dd)
{
	__count_port_discards(dd->pport);
}