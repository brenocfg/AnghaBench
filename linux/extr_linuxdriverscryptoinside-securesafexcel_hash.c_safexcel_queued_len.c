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
typedef  scalar_t__ u64 ;
struct safexcel_ahash_req {scalar_t__* len; scalar_t__* processed; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 safexcel_queued_len(struct safexcel_ahash_req *req)
{
	if (req->len[1] > req->processed[1])
		return 0xffffffff - (req->len[0] - req->processed[0]);

	return req->len[0] - req->processed[0];
}