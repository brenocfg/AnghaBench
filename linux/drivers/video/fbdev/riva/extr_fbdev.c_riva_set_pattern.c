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
struct TYPE_4__ {TYPE_1__* Patt; } ;
struct riva_par {TYPE_2__ riva; } ;
struct TYPE_3__ {int /*<<< orphan*/ * Monochrome; int /*<<< orphan*/  Color1; int /*<<< orphan*/  Color0; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_WR32 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  Patt ; 
 int /*<<< orphan*/  RIVA_FIFO_FREE (TYPE_2__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
riva_set_pattern(struct riva_par *par, int clr0, int clr1, int pat0, int pat1)
{
	RIVA_FIFO_FREE(par->riva, Patt, 4);
	NV_WR32(&par->riva.Patt->Color0, 0, clr0);
	NV_WR32(&par->riva.Patt->Color1, 0, clr1);
	NV_WR32(par->riva.Patt->Monochrome, 0, pat0);
	NV_WR32(par->riva.Patt->Monochrome, 4, pat1);
}