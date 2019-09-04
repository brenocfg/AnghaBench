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
struct TYPE_2__ {int mode; int output_mode; scalar_t__ range; scalar_t__ size; } ;
struct nv50_head_atom {TYPE_1__ olut; } ;
struct nv50_head {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
headc37d_olut(struct nv50_head *head, struct nv50_head_atom *asyh)
{
	asyh->olut.mode = 2;
	asyh->olut.size = 0;
	asyh->olut.range = 0;
	asyh->olut.output_mode = 1;
}