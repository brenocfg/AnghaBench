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
typedef  int /*<<< orphan*/  u64 ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  QUIRK_LSW32_IS_FIRST ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ likely (int) ; 
 int packing (void*,int /*<<< orphan*/ *,int,int,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,...) ; 

void sja1105_packing(void *buf, u64 *val, int start, int end,
		     size_t len, enum packing_op op)
{
	int rc = packing(buf, val, start, end, len, op, QUIRK_LSW32_IS_FIRST);

	if (likely(!rc))
		return;

	if (rc == -EINVAL) {
		pr_err("Start bit (%d) expected to be larger than end (%d)\n",
		       start, end);
	} else if (rc == -ERANGE) {
		if ((start - end + 1) > 64)
			pr_err("Field %d-%d too large for 64 bits!\n",
			       start, end);
		else
			pr_err("Cannot store %llx inside bits %d-%d (would truncate)\n",
			       *val, start, end);
	}
	dump_stack();
}