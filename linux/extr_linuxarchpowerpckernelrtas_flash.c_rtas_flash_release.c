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
struct rtas_update_flash_t {scalar_t__ status; int /*<<< orphan*/ * flist; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ FLASH_AUTH ; 
 scalar_t__ FLASH_IMG_READY ; 
 scalar_t__ flash_list_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_flash_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtas_firmware_flash_list ; 
 struct rtas_update_flash_t rtas_update_flash_data ; 
 int /*<<< orphan*/  rtas_update_flash_mutex ; 

__attribute__((used)) static int rtas_flash_release(struct inode *inode, struct file *file)
{
	struct rtas_update_flash_t *const uf = &rtas_update_flash_data;

	mutex_lock(&rtas_update_flash_mutex);

	if (uf->flist) {    
		/* File was opened in write mode for a new flash attempt */
		/* Clear saved list */
		if (rtas_firmware_flash_list) {
			free_flash_list(rtas_firmware_flash_list);
			rtas_firmware_flash_list = NULL;
		}

		if (uf->status != FLASH_AUTH)  
			uf->status = flash_list_valid(uf->flist);

		if (uf->status == FLASH_IMG_READY) 
			rtas_firmware_flash_list = uf->flist;
		else
			free_flash_list(uf->flist);

		uf->flist = NULL;
	}

	mutex_unlock(&rtas_update_flash_mutex);
	return 0;
}