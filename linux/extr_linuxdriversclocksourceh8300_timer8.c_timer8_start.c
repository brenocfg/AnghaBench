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
struct timer8_priv {int flags; } ;

/* Variables and functions */
 int FLAG_STARTED ; 
 int timer8_enable (struct timer8_priv*) ; 

__attribute__((used)) static int timer8_start(struct timer8_priv *p)
{
	int ret;

	if ((p->flags & FLAG_STARTED))
		return 0;

	ret = timer8_enable(p);
	if (!ret)
		p->flags |= FLAG_STARTED;

	return ret;
}