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
typedef  int u_char ;
struct IsdnCardState {struct BCState* bcs; } ;
struct TYPE_3__ {int dpath; } ;
struct TYPE_4__ {TYPE_1__ isar; } ;
struct BCState {TYPE_2__ hw; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct BCState *sel_bcs_isar(struct IsdnCardState *cs, u_char dpath)
{
	if ((!dpath) || (dpath == 3))
		return (NULL);
	if (cs->bcs[0].hw.isar.dpath == dpath)
		return (&cs->bcs[0]);
	if (cs->bcs[1].hw.isar.dpath == dpath)
		return (&cs->bcs[1]);
	return (NULL);
}