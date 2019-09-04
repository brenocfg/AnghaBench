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

/* Variables and functions */
 int SCC_TXRDY ; 
 int in_8 (scalar_t__) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ ,char) ; 
 scalar_t__ sccc ; 
 int /*<<< orphan*/  sccd ; 

__attribute__((used)) static void udbg_scc_putc(char c)
{
	if (sccc) {
		while ((in_8(sccc) & SCC_TXRDY) == 0)
			;
		out_8(sccd,  c);
		if (c == '\n')
			udbg_scc_putc('\r');
	}
}