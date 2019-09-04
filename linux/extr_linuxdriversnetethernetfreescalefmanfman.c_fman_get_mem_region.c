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
struct resource {int dummy; } ;
struct fman {TYPE_1__* state; } ;
struct TYPE_2__ {struct resource* res; } ;

/* Variables and functions */

struct resource *fman_get_mem_region(struct fman *fman)
{
	return fman->state->res;
}