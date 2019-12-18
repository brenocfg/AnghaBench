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
struct rc_map_table {int scancode; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 rc5_custom(struct rc_map_table *key)
{
	return (key->scancode >> 8) & 0xff;
}