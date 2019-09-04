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
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 

__attribute__((used)) static inline int mv_cesa_req_needs_cleanup(struct crypto_async_request *req,
					    int ret)
{
	/*
	 * The queue still had some space, the request was queued
	 * normally, so there's no need to clean it up.
	 */
	if (ret == -EINPROGRESS)
		return false;

	/*
	 * The queue had not space left, but since the request is
	 * flagged with CRYPTO_TFM_REQ_MAY_BACKLOG, it was added to
	 * the backlog and will be processed later. There's no need to
	 * clean it up.
	 */
	if (ret == -EBUSY)
		return false;

	/* Request wasn't queued, we need to clean it up */
	return true;
}