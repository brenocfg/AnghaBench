#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ iocharset; } ;
struct exfat_sb_info {int /*<<< orphan*/  s_lock; TYPE_1__ options; scalar_t__ nls_io; scalar_t__ nls_disk; } ;

/* Variables and functions */
 scalar_t__ exfat_default_iocharset ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  kvfree (struct exfat_sb_info*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unload_nls (scalar_t__) ; 

__attribute__((used)) static void exfat_free_super(struct exfat_sb_info *sbi)
{
	if (sbi->nls_disk)
		unload_nls(sbi->nls_disk);
	if (sbi->nls_io)
		unload_nls(sbi->nls_io);
	if (sbi->options.iocharset != exfat_default_iocharset)
		kfree(sbi->options.iocharset);
	/* mutex_init is in exfat_fill_super function. only for 3.7+ */
	mutex_destroy(&sbi->s_lock);
	kvfree(sbi);
}