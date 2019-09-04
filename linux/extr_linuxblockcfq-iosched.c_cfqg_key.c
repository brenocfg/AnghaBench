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
struct cfq_rb_root {scalar_t__ min_vdisktime; } ;
struct cfq_group {scalar_t__ vdisktime; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */

__attribute__((used)) static inline s64
cfqg_key(struct cfq_rb_root *st, struct cfq_group *cfqg)
{
	return cfqg->vdisktime - st->min_vdisktime;
}