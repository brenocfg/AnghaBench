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
struct cm_lap_msg {int offset62; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 cm_lap_get_subnet_local(struct cm_lap_msg *lap_msg)
{
	return (lap_msg->offset62 >> 3) & 0x1;
}