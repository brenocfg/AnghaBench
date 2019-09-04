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
struct host1x_syncpt_base {int dummy; } ;
struct host1x_syncpt {struct host1x_syncpt_base* base; } ;

/* Variables and functions */

struct host1x_syncpt_base *host1x_syncpt_get_base(struct host1x_syncpt *sp)
{
	return sp ? sp->base : NULL;
}