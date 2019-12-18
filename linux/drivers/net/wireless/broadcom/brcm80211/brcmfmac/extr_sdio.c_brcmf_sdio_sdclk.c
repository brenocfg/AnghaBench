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
struct brcmf_sdio {int /*<<< orphan*/  clkstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_NONE ; 
 int /*<<< orphan*/  CLK_SDONLY ; 
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int brcmf_sdio_sdclk(struct brcmf_sdio *bus, bool on)
{
	brcmf_dbg(SDIO, "Enter\n");

	if (on)
		bus->clkstate = CLK_SDONLY;
	else
		bus->clkstate = CLK_NONE;

	return 0;
}