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
struct wa_seg {int /*<<< orphan*/  tr_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_init_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void wa_seg_init(struct wa_seg *seg)
{
	usb_init_urb(&seg->tr_urb);

	/* set the remaining memory to 0. */
	memset(((void *)seg) + sizeof(seg->tr_urb), 0,
		sizeof(*seg) - sizeof(seg->tr_urb));
}