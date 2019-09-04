#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct si4713_usb_device {int* buffer; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int BUFFER_LENGTH ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int si4713_send_startup_command (struct si4713_usb_device*) ; 
 TYPE_1__* start_seq ; 

__attribute__((used)) static int si4713_start_seq(struct si4713_usb_device *radio)
{
	int retval = 0;
	int i;

	radio->buffer[0] = 0x3f;

	for (i = 0; i < ARRAY_SIZE(start_seq); i++) {
		int len = start_seq[i].len;
		const u8 *payload = start_seq[i].payload;

		memcpy(radio->buffer + 1, payload, len);
		memset(radio->buffer + len + 1, 0, BUFFER_LENGTH - 1 - len);
		retval = si4713_send_startup_command(radio);
	}

	return retval;
}