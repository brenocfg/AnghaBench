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
struct bfa_iocfc_s {TYPE_1__* bfa; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_iocfc_sm_enabling_entry(struct bfa_iocfc_s *iocfc)
{
	bfa_ioc_enable(&iocfc->bfa->ioc);
}