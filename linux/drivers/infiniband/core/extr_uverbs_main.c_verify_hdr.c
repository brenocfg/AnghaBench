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
struct uverbs_api_write_method {int req_size; int resp_size; scalar_t__ is_ex; } ;
struct ib_uverbs_ex_cmd_hdr {int provider_in_words; int provider_out_words; scalar_t__ response; scalar_t__ cmd_hdr_reserved; } ;
struct ib_uverbs_cmd_hdr {int in_words; int out_words; scalar_t__ command; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSPC ; 
 scalar_t__ IB_USER_VERBS_CMD_DESTROY_CQ ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u64_to_user_ptr (scalar_t__) ; 

__attribute__((used)) static ssize_t verify_hdr(struct ib_uverbs_cmd_hdr *hdr,
			  struct ib_uverbs_ex_cmd_hdr *ex_hdr, size_t count,
			  const struct uverbs_api_write_method *method_elm)
{
	if (method_elm->is_ex) {
		count -= sizeof(*hdr) + sizeof(*ex_hdr);

		if ((hdr->in_words + ex_hdr->provider_in_words) * 8 != count)
			return -EINVAL;

		if (hdr->in_words * 8 < method_elm->req_size)
			return -ENOSPC;

		if (ex_hdr->cmd_hdr_reserved)
			return -EINVAL;

		if (ex_hdr->response) {
			if (!hdr->out_words && !ex_hdr->provider_out_words)
				return -EINVAL;

			if (hdr->out_words * 8 < method_elm->resp_size)
				return -ENOSPC;

			if (!access_ok(u64_to_user_ptr(ex_hdr->response),
				       (hdr->out_words + ex_hdr->provider_out_words) * 8))
				return -EFAULT;
		} else {
			if (hdr->out_words || ex_hdr->provider_out_words)
				return -EINVAL;
		}

		return 0;
	}

	/* not extended command */
	if (hdr->in_words * 4 != count)
		return -EINVAL;

	if (count < method_elm->req_size + sizeof(hdr)) {
		/*
		 * rdma-core v18 and v19 have a bug where they send DESTROY_CQ
		 * with a 16 byte write instead of 24. Old kernels didn't
		 * check the size so they allowed this. Now that the size is
		 * checked provide a compatibility work around to not break
		 * those userspaces.
		 */
		if (hdr->command == IB_USER_VERBS_CMD_DESTROY_CQ &&
		    count == 16) {
			hdr->in_words = 6;
			return 0;
		}
		return -ENOSPC;
	}
	if (hdr->out_words * 4 < method_elm->resp_size)
		return -ENOSPC;

	return 0;
}