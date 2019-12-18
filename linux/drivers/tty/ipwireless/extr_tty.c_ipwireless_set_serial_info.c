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
struct tty_struct {int dummy; } ;
struct serial_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ipwireless_set_serial_info(struct tty_struct *linux_tty,
				      struct serial_struct *ss)
{
	return 0;	/* Keeps the PCMCIA scripts happy. */
}