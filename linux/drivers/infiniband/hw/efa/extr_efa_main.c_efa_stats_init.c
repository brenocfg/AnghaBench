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
struct efa_dev {int /*<<< orphan*/  stats; } ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efa_stats_init(struct efa_dev *dev)
{
	atomic64_t *s = (atomic64_t *)&dev->stats;
	int i;

	for (i = 0; i < sizeof(dev->stats) / sizeof(*s); i++, s++)
		atomic64_set(s, 0);
}