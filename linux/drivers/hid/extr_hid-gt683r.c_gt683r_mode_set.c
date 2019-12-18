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
struct gt683r_led {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GT683R_BUFFER_SIZE ; 
 int gt683r_led_snd_msg (struct gt683r_led*,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gt683r_mode_set(struct gt683r_led *led, u8 mode)
{
	int ret;
	u8 *buffer;

	buffer = kzalloc(GT683R_BUFFER_SIZE, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	buffer[0] = 0x01;
	buffer[1] = 0x02;
	buffer[2] = 0x20;
	buffer[3] = mode;
	buffer[4] = 0x01;
	ret = gt683r_led_snd_msg(led, buffer);

	kfree(buffer);
	return ret;
}