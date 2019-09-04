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
typedef  int u16 ;

/* Variables and functions */
 int LINK_SPEED_12_5G ; 
 int LINK_SPEED_25G ; 

__attribute__((used)) static inline u16 get_link_speed(u16 link_speed)
{
	return (link_speed == 1) ?
		 LINK_SPEED_12_5G : LINK_SPEED_25G;
}