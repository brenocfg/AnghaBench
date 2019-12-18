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
struct TYPE_2__ {size_t inlen; scalar_t__ inbuf; } ;
struct uverbs_attr_bundle {TYPE_1__ ucore; } ;

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
 scalar_t__ copy_from_user (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_is_buffer_cleared (scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  min (size_t,size_t) ; 

__attribute__((used)) static int uverbs_request(struct uverbs_attr_bundle *attrs, void *req,
			  size_t req_len)
{
	if (copy_from_user(req, attrs->ucore.inbuf,
			   min(attrs->ucore.inlen, req_len)))
		return -EFAULT;

	if (attrs->ucore.inlen < req_len) {
		memset(req + attrs->ucore.inlen, 0,
		       req_len - attrs->ucore.inlen);
	} else if (attrs->ucore.inlen > req_len) {
		if (!ib_is_buffer_cleared(attrs->ucore.inbuf + req_len,
					  attrs->ucore.inlen - req_len))
			return -EOPNOTSUPP;
	}
	return 0;
}