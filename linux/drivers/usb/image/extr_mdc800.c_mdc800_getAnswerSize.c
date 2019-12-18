#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pic_len; } ;

/* Variables and functions */
 TYPE_1__* mdc800 ; 

__attribute__((used)) static int mdc800_getAnswerSize (char command)
{
	switch ((unsigned char) command)
	{
		case 0x2a:
		case 0x49:
		case 0x51:
		case 0x0d:
		case 0x20:
		case 0x07:
		case 0x01:
		case 0x25:
		case 0x00:
			return 8;

		case 0x05:
		case 0x3e:
			return mdc800->pic_len;

		case 0x09:
			return 4096;

		default:
			return 0;
	}
}