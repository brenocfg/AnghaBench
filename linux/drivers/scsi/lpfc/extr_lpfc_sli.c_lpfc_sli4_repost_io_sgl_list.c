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
struct TYPE_2__ {int /*<<< orphan*/  io_xri_cnt; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_io_buf_flush (struct lpfc_hba*,int /*<<< orphan*/ *) ; 
 int lpfc_sli4_post_io_sgl_list (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_nblist ; 

__attribute__((used)) static int
lpfc_sli4_repost_io_sgl_list(struct lpfc_hba *phba)
{
	LIST_HEAD(post_nblist);
	int num_posted, rc = 0;

	/* get all NVME buffers need to repost to a local list */
	lpfc_io_buf_flush(phba, &post_nblist);

	/* post the list of nvme buffer sgls to port if available */
	if (!list_empty(&post_nblist)) {
		num_posted = lpfc_sli4_post_io_sgl_list(
			phba, &post_nblist, phba->sli4_hba.io_xri_cnt);
		/* failed to post any nvme buffer, return error */
		if (num_posted == 0)
			rc = -EIO;
	}
	return rc;
}