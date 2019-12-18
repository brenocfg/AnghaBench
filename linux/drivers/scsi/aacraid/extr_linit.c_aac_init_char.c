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
 int /*<<< orphan*/  aac_cfg_fops ; 
 scalar_t__ aac_cfg_major ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ register_chrdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aac_init_char(void)
{
	aac_cfg_major = register_chrdev(0, "aac", &aac_cfg_fops);
	if (aac_cfg_major < 0) {
		pr_err("aacraid: unable to register \"aac\" device.\n");
	}
}