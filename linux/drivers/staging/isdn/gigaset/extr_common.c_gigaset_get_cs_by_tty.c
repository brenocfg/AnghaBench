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
struct tty_struct {TYPE_1__* driver; scalar_t__ index; } ;
struct cardstate {int dummy; } ;
struct TYPE_2__ {scalar_t__ minor_start; } ;

/* Variables and functions */
 struct cardstate* gigaset_get_cs_by_minor (scalar_t__) ; 

struct cardstate *gigaset_get_cs_by_tty(struct tty_struct *tty)
{
	return gigaset_get_cs_by_minor(tty->index + tty->driver->minor_start);
}