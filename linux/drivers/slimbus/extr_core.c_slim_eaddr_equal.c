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
struct slim_eaddr {scalar_t__ manf_id; scalar_t__ prod_code; scalar_t__ dev_index; scalar_t__ instance; } ;

/* Variables and functions */

__attribute__((used)) static bool slim_eaddr_equal(struct slim_eaddr *a, struct slim_eaddr *b)
{
	return (a->manf_id == b->manf_id &&
		a->prod_code == b->prod_code &&
		a->dev_index == b->dev_index &&
		a->instance == b->instance);
}