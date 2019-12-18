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
struct visorhba_devdata {TYPE_1__* pending; } ;
struct uiscmdrsp {int dummy; } ;
struct TYPE_2__ {struct uiscmdrsp cmdrsp; scalar_t__ sent; } ;

/* Variables and functions */

__attribute__((used)) static struct uiscmdrsp *get_scsipending_cmdrsp(struct visorhba_devdata *ddata,
						int ent)
{
	if (ddata->pending[ent].sent)
		return &ddata->pending[ent].cmdrsp;

	return NULL;
}