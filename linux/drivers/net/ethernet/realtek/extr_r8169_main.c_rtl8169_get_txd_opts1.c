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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int NUM_TX_DESC ; 
 int RingEnd ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static __le32 rtl8169_get_txd_opts1(u32 opts0, u32 len, unsigned int entry)
{
	u32 status = opts0 | len;

	if (entry == NUM_TX_DESC - 1)
		status |= RingEnd;

	return cpu_to_le32(status);
}