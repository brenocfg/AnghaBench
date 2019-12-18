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
struct macb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDLE ; 
 int MACB_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACB_MDIO_TIMEOUT ; 
 int /*<<< orphan*/  MACB_READ_NSR ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct macb*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int macb_mdio_wait_for_idle(struct macb *bp)
{
	u32 val;

	return readx_poll_timeout(MACB_READ_NSR, bp, val, val & MACB_BIT(IDLE),
				  1, MACB_MDIO_TIMEOUT);
}