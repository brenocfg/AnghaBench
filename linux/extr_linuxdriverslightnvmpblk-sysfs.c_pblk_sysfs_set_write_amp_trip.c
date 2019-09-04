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
struct pblk {int /*<<< orphan*/  gc_wa; void* gc_rst_wa; int /*<<< orphan*/  pad_wa; void* pad_rst_wa; int /*<<< orphan*/  user_wa; void* user_rst_wa; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 void* atomic64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,int*) ; 
 size_t strcspn (char const*,char*) ; 

__attribute__((used)) static ssize_t pblk_sysfs_set_write_amp_trip(struct pblk *pblk,
			const char *page, size_t len)
{
	size_t c_len;
	int reset_value;

	c_len = strcspn(page, "\n");
	if (c_len >= len)
		return -EINVAL;

	if (kstrtouint(page, 0, &reset_value))
		return -EINVAL;

	if (reset_value !=  0)
		return -EINVAL;

	pblk->user_rst_wa = atomic64_read(&pblk->user_wa);
	pblk->pad_rst_wa = atomic64_read(&pblk->pad_wa);
	pblk->gc_rst_wa = atomic64_read(&pblk->gc_wa);

	return len;
}