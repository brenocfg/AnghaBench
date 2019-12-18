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
struct siw_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  laddr; } ;
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */

__attribute__((used)) static inline void siw_copy_sgl(struct ib_sge *sge, struct siw_sge *siw_sge,
				int num_sge)
{
	while (num_sge--) {
		siw_sge->laddr = sge->addr;
		siw_sge->length = sge->length;
		siw_sge->lkey = sge->lkey;

		siw_sge++;
		sge++;
	}
}