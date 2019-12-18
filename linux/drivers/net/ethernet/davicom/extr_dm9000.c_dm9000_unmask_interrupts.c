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
struct board_info {int /*<<< orphan*/  imr_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_IMR ; 
 int /*<<< orphan*/  iow (struct board_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dm9000_unmask_interrupts(struct board_info *db)
{
	iow(db, DM9000_IMR, db->imr_all);
}