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
struct ksz_desc_info {int alloc; int mask; } ;

/* Variables and functions */
 int MIN_DESC_SHIFT ; 
 int /*<<< orphan*/  pr_alert (char*) ; 

__attribute__((used)) static void ksz_check_desc_num(struct ksz_desc_info *info)
{
#define MIN_DESC_SHIFT  2

	int alloc = info->alloc;
	int shift;

	shift = 0;
	while (!(alloc & 1)) {
		shift++;
		alloc >>= 1;
	}
	if (alloc != 1 || shift < MIN_DESC_SHIFT) {
		pr_alert("Hardware descriptor numbers not right!\n");
		while (alloc) {
			shift++;
			alloc >>= 1;
		}
		if (shift < MIN_DESC_SHIFT)
			shift = MIN_DESC_SHIFT;
		alloc = 1 << shift;
		info->alloc = alloc;
	}
	info->mask = info->alloc - 1;
}