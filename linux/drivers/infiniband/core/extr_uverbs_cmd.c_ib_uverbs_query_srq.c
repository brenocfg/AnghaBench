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
struct uverbs_attr_bundle {int dummy; } ;
struct ib_uverbs_query_srq_resp {int /*<<< orphan*/  srq_limit; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; } ;
struct ib_uverbs_query_srq {int /*<<< orphan*/  srq_handle; } ;
struct ib_srq_attr {int /*<<< orphan*/  srq_limit; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; } ;
struct ib_srq {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UVERBS_OBJECT_SRQ ; 
 int ib_query_srq (struct ib_srq*,struct ib_srq_attr*) ; 
 int /*<<< orphan*/  memset (struct ib_uverbs_query_srq_resp*,int /*<<< orphan*/ ,int) ; 
 struct ib_srq* uobj_get_obj_read (struct ib_srq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uobj_put_obj_read (struct ib_srq*) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_query_srq*,int) ; 
 int uverbs_response (struct uverbs_attr_bundle*,struct ib_uverbs_query_srq_resp*,int) ; 

__attribute__((used)) static int ib_uverbs_query_srq(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_query_srq      cmd;
	struct ib_uverbs_query_srq_resp resp;
	struct ib_srq_attr              attr;
	struct ib_srq                   *srq;
	int                             ret;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	srq = uobj_get_obj_read(srq, UVERBS_OBJECT_SRQ, cmd.srq_handle, attrs);
	if (!srq)
		return -EINVAL;

	ret = ib_query_srq(srq, &attr);

	uobj_put_obj_read(srq);

	if (ret)
		return ret;

	memset(&resp, 0, sizeof resp);

	resp.max_wr    = attr.max_wr;
	resp.max_sge   = attr.max_sge;
	resp.srq_limit = attr.srq_limit;

	return uverbs_response(attrs, &resp, sizeof(resp));
}