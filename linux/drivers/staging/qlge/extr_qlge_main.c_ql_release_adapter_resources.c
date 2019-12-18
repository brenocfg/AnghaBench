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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_free_irq (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_free_mem_resources (struct ql_adapter*) ; 

__attribute__((used)) static void ql_release_adapter_resources(struct ql_adapter *qdev)
{
	ql_free_mem_resources(qdev);
	ql_free_irq(qdev);
}