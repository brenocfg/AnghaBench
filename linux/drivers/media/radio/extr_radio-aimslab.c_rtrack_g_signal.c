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
typedef  int u32 ;
struct radio_isa_card {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 rtrack_g_signal(struct radio_isa_card *isa)
{
	/* bit set = no signal present */
	return 0xffff * !(inb(isa->io) & 2);
}