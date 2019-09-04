#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  scn; int /*<<< orphan*/  c; } ;
struct esca_entry {TYPE_1__ sigp_ctrl; int /*<<< orphan*/  sda; } ;
struct TYPE_4__ {int /*<<< orphan*/  scn; int /*<<< orphan*/  c; } ;
struct bsca_entry {TYPE_2__ sigp_ctrl; int /*<<< orphan*/  sda; } ;

/* Variables and functions */

__attribute__((used)) static inline void sca_copy_entry(struct esca_entry *d, struct bsca_entry *s)
{
	d->sda = s->sda;
	d->sigp_ctrl.c = s->sigp_ctrl.c;
	d->sigp_ctrl.scn = s->sigp_ctrl.scn;
}