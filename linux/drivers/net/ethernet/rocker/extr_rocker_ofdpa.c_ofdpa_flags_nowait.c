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
 int OFDPA_OP_FLAG_NOWAIT ; 

__attribute__((used)) static bool ofdpa_flags_nowait(int flags)
{
	return flags & OFDPA_OP_FLAG_NOWAIT;
}