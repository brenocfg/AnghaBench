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
struct l4 {scalar_t__ port; } ;
struct gameport {struct l4* port_data; } ;

/* Variables and functions */
 int GAMEPORT_MODE_COOKED ; 
 int /*<<< orphan*/  L4_PORT ; 
 int /*<<< orphan*/  L4_SELECT_ANALOG ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l4_open(struct gameport *gameport, int mode)
{
	struct l4 *l4 = gameport->port_data;

        if (l4->port != 0 && mode != GAMEPORT_MODE_COOKED)
		return -1;
	outb(L4_SELECT_ANALOG, L4_PORT);
	return 0;
}