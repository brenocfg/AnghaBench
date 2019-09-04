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
 int SEES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_SDMA0_DISALLOWED_PACKET ; 
 int /*<<< orphan*/  TX_SDMA15_DISALLOWED_PACKET ; 

__attribute__((used)) static inline int disallowed_pkt_err(int posn)
{
	return (posn >= SEES(TX_SDMA0_DISALLOWED_PACKET) &&
		posn <= SEES(TX_SDMA15_DISALLOWED_PACKET));
}