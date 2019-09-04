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
struct aead_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 

__attribute__((used)) static inline void async_done_continue(struct aead_request *req, int err,
				       int (*cont)(struct aead_request *))
{
	if (!err)
		err = cont(req);

	if (err != -EINPROGRESS && err != -EBUSY)
		aead_request_complete(req, err);
}