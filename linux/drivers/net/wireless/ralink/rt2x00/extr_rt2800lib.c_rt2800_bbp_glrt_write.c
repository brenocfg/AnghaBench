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
typedef  int /*<<< orphan*/  u8 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void rt2800_bbp_glrt_write(struct rt2x00_dev *rt2x00dev,
				  const u8 reg, const u8 value)
{
	rt2800_bbp_write(rt2x00dev, 195, reg);
	rt2800_bbp_write(rt2x00dev, 196, value);
}