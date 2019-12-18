#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t iov_offset; TYPE_1__* bvec; } ;
struct nvme_tcp_request {TYPE_2__ iter; } ;
struct TYPE_3__ {size_t bv_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t nvme_tcp_req_cur_offset(struct nvme_tcp_request *req)
{
	return req->iter.bvec->bv_offset + req->iter.iov_offset;
}