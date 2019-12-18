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
struct sur40_state {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SUR40_ACCEL_CAPS ; 
 int /*<<< orphan*/  SUR40_GET_VERSION ; 
 int /*<<< orphan*/  SUR40_SENSOR_CAPS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int sur40_command (struct sur40_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sur40_init(struct sur40_state *dev)
{
	int result;
	u8 *buffer;

	buffer = kmalloc(24, GFP_KERNEL);
	if (!buffer) {
		result = -ENOMEM;
		goto error;
	}

	/* stupidly replay the original MS driver init sequence */
	result = sur40_command(dev, SUR40_GET_VERSION, 0x00, buffer, 12);
	if (result < 0)
		goto error;

	result = sur40_command(dev, SUR40_GET_VERSION, 0x01, buffer, 12);
	if (result < 0)
		goto error;

	result = sur40_command(dev, SUR40_GET_VERSION, 0x02, buffer, 12);
	if (result < 0)
		goto error;

	result = sur40_command(dev, SUR40_SENSOR_CAPS, 0x00, buffer, 24);
	if (result < 0)
		goto error;

	result = sur40_command(dev, SUR40_ACCEL_CAPS, 0x00, buffer, 5);
	if (result < 0)
		goto error;

	result = sur40_command(dev, SUR40_GET_VERSION, 0x03, buffer, 12);

	/*
	 * Discard the result buffer - no known data inside except
	 * some version strings, maybe extract these sometime...
	 */
error:
	kfree(buffer);
	return result;
}