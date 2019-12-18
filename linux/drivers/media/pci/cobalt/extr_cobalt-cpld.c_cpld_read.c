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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct cobalt {int /*<<< orphan*/  bar1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADRS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cobalt_bus_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 cpld_read(struct cobalt *cobalt, u32 offset)
{
	return cobalt_bus_read32(cobalt->bar1, ADRS(offset));
}