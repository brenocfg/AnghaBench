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
struct ql3_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_petbi_reset_ex (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_petbi_start_neg_ex (struct ql3_adapter*) ; 

__attribute__((used)) static void ql_petbi_init_ex(struct ql3_adapter *qdev)
{
	ql_petbi_reset_ex(qdev);
	ql_petbi_start_neg_ex(qdev);
}