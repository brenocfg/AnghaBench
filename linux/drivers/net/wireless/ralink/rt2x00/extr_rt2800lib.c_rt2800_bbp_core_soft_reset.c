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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBP4_BANDWIDTH ; 
 int rt2800_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rt2800_bbp_core_soft_reset(struct rt2x00_dev *rt2x00dev,
				       bool set_bw, bool is_ht40)
{
	u8 bbp_val;

	bbp_val = rt2800_bbp_read(rt2x00dev, 21);
	bbp_val |= 0x1;
	rt2800_bbp_write(rt2x00dev, 21, bbp_val);
	usleep_range(100, 200);

	if (set_bw) {
		bbp_val = rt2800_bbp_read(rt2x00dev, 4);
		rt2x00_set_field8(&bbp_val, BBP4_BANDWIDTH, 2 * is_ht40);
		rt2800_bbp_write(rt2x00dev, 4, bbp_val);
		usleep_range(100, 200);
	}

	bbp_val = rt2800_bbp_read(rt2x00dev, 21);
	bbp_val &= (~0x1);
	rt2800_bbp_write(rt2x00dev, 21, bbp_val);
	usleep_range(100, 200);
}