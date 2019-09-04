#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* encodebuf; } ;
typedef  TYPE_1__ isdn_v110_stream ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void
isdn_v110_close(isdn_v110_stream *v)
{
	if (v == NULL)
		return;
#ifdef ISDN_V110_DEBUG
	printk(KERN_DEBUG "v110 close\n");
#endif
	kfree(v->encodebuf);
	kfree(v);
}