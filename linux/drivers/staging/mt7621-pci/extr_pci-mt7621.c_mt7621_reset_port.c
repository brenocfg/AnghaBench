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
struct mt7621_pcie_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mt7621_control_assert (struct mt7621_pcie_port*) ; 
 int /*<<< orphan*/  mt7621_control_deassert (struct mt7621_pcie_port*) ; 

__attribute__((used)) static void mt7621_reset_port(struct mt7621_pcie_port *port)
{
	mt7621_control_assert(port);
	msleep(100);
	mt7621_control_deassert(port);
}