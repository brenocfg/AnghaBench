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
struct pblk {int min_write_pgs; int max_write_pgs; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pblk_is_oob_meta_supported (struct pblk*) ; 
 int /*<<< orphan*/  pblk_set_sec_per_write (struct pblk*,int) ; 
 size_t strcspn (char const*,char*) ; 

__attribute__((used)) static ssize_t pblk_sysfs_set_sec_per_write(struct pblk *pblk,
					     const char *page, size_t len)
{
	size_t c_len;
	int sec_per_write;

	c_len = strcspn(page, "\n");
	if (c_len >= len)
		return -EINVAL;

	if (kstrtouint(page, 0, &sec_per_write))
		return -EINVAL;

	if (!pblk_is_oob_meta_supported(pblk)) {
		/* For packed metadata case it is
		 * not allowed to change sec_per_write.
		 */
		return -EINVAL;
	}

	if (sec_per_write < pblk->min_write_pgs
				|| sec_per_write > pblk->max_write_pgs
				|| sec_per_write % pblk->min_write_pgs != 0)
		return -EINVAL;

	pblk_set_sec_per_write(pblk, sec_per_write);

	return len;
}