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
typedef  int /*<<< orphan*/  u32 ;
struct se_hba {int /*<<< orphan*/  hba_id; struct fd_host* hba_ptr; } ;
struct fd_host {int /*<<< orphan*/  fd_host_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FD_VERSION ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TARGET_CORE_VERSION ; 
 struct fd_host* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int fd_attach_hba(struct se_hba *hba, u32 host_id)
{
	struct fd_host *fd_host;

	fd_host = kzalloc(sizeof(struct fd_host), GFP_KERNEL);
	if (!fd_host) {
		pr_err("Unable to allocate memory for struct fd_host\n");
		return -ENOMEM;
	}

	fd_host->fd_host_id = host_id;

	hba->hba_ptr = fd_host;

	pr_debug("CORE_HBA[%d] - TCM FILEIO HBA Driver %s on Generic"
		" Target Core Stack %s\n", hba->hba_id, FD_VERSION,
		TARGET_CORE_VERSION);
	pr_debug("CORE_HBA[%d] - Attached FILEIO HBA: %u to Generic\n",
		hba->hba_id, fd_host->fd_host_id);

	return 0;
}