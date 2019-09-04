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
struct w8001_coord {int x; int y; int tsw; } ;

/* Variables and functions */

__attribute__((used)) static void parse_single_touch(u8 *data, struct w8001_coord *coord)
{
	coord->x = (data[1] << 7) | data[2];
	coord->y = (data[3] << 7) | data[4];
	coord->tsw = data[0] & 0x01;
}