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
struct ili9320_platdata {int /*<<< orphan*/  (* reset ) (int) ;} ;
struct ili9320 {struct ili9320_platdata* platdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  stub3 (int) ; 

__attribute__((used)) static void ili9320_reset(struct ili9320 *lcd)
{
	struct ili9320_platdata *cfg = lcd->platdata;

	cfg->reset(1);
	mdelay(50);

	cfg->reset(0);
	mdelay(50);

	cfg->reset(1);
	mdelay(100);
}