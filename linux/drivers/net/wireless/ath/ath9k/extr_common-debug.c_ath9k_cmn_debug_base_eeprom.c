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
struct dentry {int dummy; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct ath_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_base_eeprom ; 

void ath9k_cmn_debug_base_eeprom(struct dentry *debugfs_phy,
				 struct ath_hw *ah)
{
	debugfs_create_file("base_eeprom", 0400, debugfs_phy, ah,
			    &fops_base_eeprom);
}