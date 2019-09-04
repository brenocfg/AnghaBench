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
typedef  int u8 ;

/* Variables and functions */
 int ISER_SIGNAL_CMD_COUNT ; 

__attribute__((used)) static inline bool iser_signal_comp(u8 sig_count)
{
	return ((sig_count % ISER_SIGNAL_CMD_COUNT) == 0);
}