#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* chips_init_ar ; 
 TYPE_1__* chips_init_cr ; 
 TYPE_1__* chips_init_fr ; 
 TYPE_1__* chips_init_gr ; 
 TYPE_1__* chips_init_sr ; 
 TYPE_1__* chips_init_xr ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  write_ar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_gr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_xr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chips_hw_init(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(chips_init_xr); ++i)
		write_xr(chips_init_xr[i].addr, chips_init_xr[i].data);
	outb(0x29, 0x3c2); /* set misc output reg */
	for (i = 0; i < ARRAY_SIZE(chips_init_sr); ++i)
		write_sr(chips_init_sr[i].addr, chips_init_sr[i].data);
	for (i = 0; i < ARRAY_SIZE(chips_init_gr); ++i)
		write_gr(chips_init_gr[i].addr, chips_init_gr[i].data);
	for (i = 0; i < ARRAY_SIZE(chips_init_ar); ++i)
		write_ar(chips_init_ar[i].addr, chips_init_ar[i].data);
	for (i = 0; i < ARRAY_SIZE(chips_init_cr); ++i)
		write_cr(chips_init_cr[i].addr, chips_init_cr[i].data);
	for (i = 0; i < ARRAY_SIZE(chips_init_fr); ++i)
		write_fr(chips_init_fr[i].addr, chips_init_fr[i].data);
}