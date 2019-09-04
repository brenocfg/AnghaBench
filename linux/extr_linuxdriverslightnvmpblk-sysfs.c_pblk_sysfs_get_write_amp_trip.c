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
struct pblk {scalar_t__ pad_rst_wa; int /*<<< orphan*/  pad_wa; scalar_t__ gc_rst_wa; int /*<<< orphan*/  gc_wa; scalar_t__ user_rst_wa; int /*<<< orphan*/  user_wa; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_get_write_amp (scalar_t__,scalar_t__,scalar_t__,char*) ; 

__attribute__((used)) static ssize_t pblk_sysfs_get_write_amp_trip(struct pblk *pblk, char *page)
{
	return pblk_get_write_amp(
		atomic64_read(&pblk->user_wa) - pblk->user_rst_wa,
		atomic64_read(&pblk->gc_wa) - pblk->gc_rst_wa,
		atomic64_read(&pblk->pad_wa) - pblk->pad_rst_wa, page);
}