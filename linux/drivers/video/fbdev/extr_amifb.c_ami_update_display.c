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
struct amifb_par {int /*<<< orphan*/  ddfstop; int /*<<< orphan*/  ddfstrt; int /*<<< orphan*/  bpl2mod; int /*<<< orphan*/  bpl1mod; int /*<<< orphan*/  bplcon1; } ;
struct TYPE_2__ {int /*<<< orphan*/  ddfstop; int /*<<< orphan*/  ddfstrt; int /*<<< orphan*/  bpl2mod; int /*<<< orphan*/  bpl1mod; int /*<<< orphan*/  bplcon1; } ;

/* Variables and functions */
 TYPE_1__ custom ; 
 int /*<<< orphan*/  ddfstop2hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddfstrt2hw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ami_update_display(const struct amifb_par *par)
{
	custom.bplcon1 = par->bplcon1;
	custom.bpl1mod = par->bpl1mod;
	custom.bpl2mod = par->bpl2mod;
	custom.ddfstrt = ddfstrt2hw(par->ddfstrt);
	custom.ddfstop = ddfstop2hw(par->ddfstop);
}