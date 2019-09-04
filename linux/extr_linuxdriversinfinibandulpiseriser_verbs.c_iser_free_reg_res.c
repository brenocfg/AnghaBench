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
struct iser_reg_resources {int /*<<< orphan*/  mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dereg_mr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iser_free_reg_res(struct iser_reg_resources *rsc)
{
	ib_dereg_mr(rsc->mr);
}