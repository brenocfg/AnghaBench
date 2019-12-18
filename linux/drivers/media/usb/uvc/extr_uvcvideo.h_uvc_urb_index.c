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
typedef  int u32 ;
struct uvc_urb {TYPE_1__* stream; } ;
struct TYPE_2__ {struct uvc_urb const* uvc_urb; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 uvc_urb_index(const struct uvc_urb *uvc_urb)
{
	return uvc_urb - &uvc_urb->stream->uvc_urb[0];
}