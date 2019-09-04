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
struct tpm_chip {scalar_t__* bios_dir; } ;
struct inode {int /*<<< orphan*/ * i_private; } ;

/* Variables and functions */
 int TPM_NUM_EVENT_LOG_FILES ; 
 struct inode* d_inode (scalar_t__) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  securityfs_remove (scalar_t__) ; 

void tpm_bios_log_teardown(struct tpm_chip *chip)
{
	int i;
	struct inode *inode;

	/* securityfs_remove currently doesn't take care of handling sync
	 * between removal and opening of pseudo files. To handle this, a
	 * workaround is added by making i_private = NULL here during removal
	 * and to check it during open(), both within inode_lock()/unlock().
	 * This design ensures that open() either safely gets kref or fails.
	 */
	for (i = (TPM_NUM_EVENT_LOG_FILES - 1); i >= 0; i--) {
		if (chip->bios_dir[i]) {
			inode = d_inode(chip->bios_dir[i]);
			inode_lock(inode);
			inode->i_private = NULL;
			inode_unlock(inode);
			securityfs_remove(chip->bios_dir[i]);
		}
	}
}