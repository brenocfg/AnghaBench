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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ purgatory_backup_dest ; 
 scalar_t__ purgatory_backup_src ; 
 int /*<<< orphan*/  purgatory_backup_sz ; 

__attribute__((used)) static int copy_backup_region(void)
{
	if (purgatory_backup_dest) {
		memcpy((void *)purgatory_backup_dest,
		       (void *)purgatory_backup_src, purgatory_backup_sz);
	}
	return 0;
}