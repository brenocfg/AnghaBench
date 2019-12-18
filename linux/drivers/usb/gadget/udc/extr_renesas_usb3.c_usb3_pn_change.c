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
struct renesas_usb3 {int num_usb3_eps; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  USB3_PIPE_COM ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb3_pn_change(struct renesas_usb3 *usb3, int num)
{
	if (num == 0 || num > usb3->num_usb3_eps)
		return -ENXIO;

	usb3_write(usb3, num, USB3_PIPE_COM);

	return 0;
}