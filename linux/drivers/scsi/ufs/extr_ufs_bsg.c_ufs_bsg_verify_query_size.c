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
struct ufs_hba {int /*<<< orphan*/  dev; } ;
struct ufs_bsg_request {int dummy; } ;
struct ufs_bsg_reply {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ufs_bsg_verify_query_size(struct ufs_hba *hba,
				     unsigned int request_len,
				     unsigned int reply_len)
{
	int min_req_len = sizeof(struct ufs_bsg_request);
	int min_rsp_len = sizeof(struct ufs_bsg_reply);

	if (min_req_len > request_len || min_rsp_len > reply_len) {
		dev_err(hba->dev, "not enough space assigned\n");
		return -EINVAL;
	}

	return 0;
}