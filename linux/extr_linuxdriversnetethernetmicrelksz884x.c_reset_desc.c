#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ hw_owned; } ;
union desc_stat {int /*<<< orphan*/  data; TYPE_1__ rx; } ;
struct ksz_desc {TYPE_3__* phw; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_2__ ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void reset_desc(struct ksz_desc *desc, union desc_stat status)
{
	status.rx.hw_owned = 0;
	desc->phw->ctrl.data = cpu_to_le32(status.data);
}