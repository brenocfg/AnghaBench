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
struct uverbs_req_iter {scalar_t__ end; scalar_t__ cur; } ;
struct TYPE_2__ {size_t inlen; scalar_t__ inbuf; } ;
struct uverbs_attr_bundle {TYPE_1__ ucore; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOSPC ; 
 scalar_t__ copy_from_user (void*,scalar_t__,size_t) ; 

__attribute__((used)) static int uverbs_request_start(struct uverbs_attr_bundle *attrs,
				struct uverbs_req_iter *iter,
				void *req,
				size_t req_len)
{
	if (attrs->ucore.inlen < req_len)
		return -ENOSPC;

	if (copy_from_user(req, attrs->ucore.inbuf, req_len))
		return -EFAULT;

	iter->cur = attrs->ucore.inbuf + req_len;
	iter->end = attrs->ucore.inbuf + attrs->ucore.inlen;
	return 0;
}