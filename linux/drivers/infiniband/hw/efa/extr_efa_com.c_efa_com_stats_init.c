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
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;
struct efa_com_dev {TYPE_1__ aq; } ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efa_com_stats_init(struct efa_com_dev *edev)
{
	atomic64_t *s = (atomic64_t *)&edev->aq.stats;
	int i;

	for (i = 0; i < sizeof(edev->aq.stats) / sizeof(*s); i++, s++)
		atomic64_set(s, 0);
}