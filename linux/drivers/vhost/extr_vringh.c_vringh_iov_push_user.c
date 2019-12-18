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
struct vringh_kiov {int dummy; } ;
struct vringh_iov {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  vringh_iov_xfer (struct vringh_kiov*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfer_to_user ; 

ssize_t vringh_iov_push_user(struct vringh_iov *wiov,
			     const void *src, size_t len)
{
	return vringh_iov_xfer((struct vringh_kiov *)wiov,
			       (void *)src, len, xfer_to_user);
}