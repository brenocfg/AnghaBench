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
struct brcmf_pub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_debugfs_add_entry (struct brcmf_pub*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_feat_debugfs_read ; 
 int /*<<< orphan*/  brcmf_feat_fwcap_debugfs_read ; 

void brcmf_feat_debugfs_create(struct brcmf_pub *drvr)
{
	brcmf_debugfs_add_entry(drvr, "features", brcmf_feat_debugfs_read);
	brcmf_debugfs_add_entry(drvr, "fwcap", brcmf_feat_fwcap_debugfs_read);
}