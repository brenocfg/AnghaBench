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
typedef  int __u32 ;

/* Variables and functions */
 int GRCAN_EFF_FRAME_MAX_BITS ; 

__attribute__((used)) static inline u32 grcan_ongoing_wait_usecs(__u32 bitrate)
{
	return 1000000 * 3 * GRCAN_EFF_FRAME_MAX_BITS / bitrate;
}