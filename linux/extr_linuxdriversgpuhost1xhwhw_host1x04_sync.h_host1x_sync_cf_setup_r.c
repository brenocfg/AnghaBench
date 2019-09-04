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

/* Variables and functions */
 unsigned int REGISTER_STRIDE ; 

__attribute__((used)) static inline u32 host1x_sync_cf_setup_r(unsigned int channel)
{
	return 0xc00 + channel * REGISTER_STRIDE;
}