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
struct uvc_fh {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ UVC_HANDLE_ACTIVE ; 

__attribute__((used)) static int uvc_has_privileges(struct uvc_fh *handle)
{
	return handle->state == UVC_HANDLE_ACTIVE;
}