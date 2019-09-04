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
struct pxrc {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxrc_free_urb(void *_pxrc)
{
	struct pxrc *pxrc = _pxrc;

	usb_free_urb(pxrc->urb);
}