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
struct input_dev {int /*<<< orphan*/ * timestamp; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 size_t INPUT_CLK_BOOT ; 
 size_t INPUT_CLK_MONO ; 
 size_t INPUT_CLK_REAL ; 
 int /*<<< orphan*/  TK_OFFS_BOOT ; 
 int /*<<< orphan*/  ktime_mono_to_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_mono_to_real (int /*<<< orphan*/ ) ; 

void input_set_timestamp(struct input_dev *dev, ktime_t timestamp)
{
	dev->timestamp[INPUT_CLK_MONO] = timestamp;
	dev->timestamp[INPUT_CLK_REAL] = ktime_mono_to_real(timestamp);
	dev->timestamp[INPUT_CLK_BOOT] = ktime_mono_to_any(timestamp,
							   TK_OFFS_BOOT);
}