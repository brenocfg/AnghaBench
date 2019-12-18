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
struct bna_ioceth {TYPE_1__* bna; } ;
struct TYPE_2__ {int /*<<< orphan*/  bnad; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnad_cb_ioceth_failed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_ioceth_sm_failed_entry(struct bna_ioceth *ioceth)
{
	bnad_cb_ioceth_failed(ioceth->bna->bnad);
}