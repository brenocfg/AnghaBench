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
struct uvc_fh {int dummy; } ;

/* Variables and functions */
 int __uvc_ctrl_commit (struct uvc_fh*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int uvc_ctrl_rollback(struct uvc_fh *handle)
{
	return __uvc_ctrl_commit(handle, 1, NULL, 0);
}