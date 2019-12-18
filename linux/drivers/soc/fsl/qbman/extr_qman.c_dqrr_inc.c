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
struct qm_dqrr_entry {int dummy; } ;

/* Variables and functions */
 struct qm_dqrr_entry const* dqrr_carryclear (struct qm_dqrr_entry const*) ; 

__attribute__((used)) static const struct qm_dqrr_entry *dqrr_inc(const struct qm_dqrr_entry *e)
{
	return dqrr_carryclear(e + 1);
}