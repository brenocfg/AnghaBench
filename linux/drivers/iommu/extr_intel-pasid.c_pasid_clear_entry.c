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
struct pasid_entry {int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pasid_clear_entry(struct pasid_entry *pe)
{
	WRITE_ONCE(pe->val[0], 0);
	WRITE_ONCE(pe->val[1], 0);
	WRITE_ONCE(pe->val[2], 0);
	WRITE_ONCE(pe->val[3], 0);
	WRITE_ONCE(pe->val[4], 0);
	WRITE_ONCE(pe->val[5], 0);
	WRITE_ONCE(pe->val[6], 0);
	WRITE_ONCE(pe->val[7], 0);
}