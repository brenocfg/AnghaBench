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
struct cppi_descriptor {int /*<<< orphan*/  hw_options; int /*<<< orphan*/  hw_off_len; int /*<<< orphan*/  hw_bufp; int /*<<< orphan*/  hw_next; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cppi_dump_rxbd(const char *tag, struct cppi_descriptor *bd)
{
	pr_debug("RXBD/%s %08x: "
			"nxt %08x buf %08x off.blen %08x opt.plen %08x\n",
			tag, bd->dma,
			bd->hw_next, bd->hw_bufp, bd->hw_off_len,
			bd->hw_options);
}