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

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  QUIRK_LSW32_IS_FIRST ; 
 int /*<<< orphan*/  UNPACK ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ likely (int) ; 
 int packing (void*,int /*<<< orphan*/ *,int,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

void sja1105_unpack(const void *buf, u64 *val, int start, int end, size_t len)
{
	int rc = packing((void *)buf, val, start, end, len,
			 UNPACK, QUIRK_LSW32_IS_FIRST);

	if (likely(!rc))
		return;

	if (rc == -EINVAL)
		pr_err("Start bit (%d) expected to be larger than end (%d)\n",
		       start, end);
	else if (rc == -ERANGE)
		pr_err("Field %d-%d too large for 64 bits!\n",
		       start, end);
	dump_stack();
}