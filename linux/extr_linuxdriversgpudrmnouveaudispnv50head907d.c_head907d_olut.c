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
struct TYPE_2__ {int mode; } ;
struct nv50_head_atom {TYPE_1__ olut; } ;
struct nv50_head {int dummy; } ;

/* Variables and functions */

void
head907d_olut(struct nv50_head *head, struct nv50_head_atom *asyh)
{
	asyh->olut.mode = 7;
}