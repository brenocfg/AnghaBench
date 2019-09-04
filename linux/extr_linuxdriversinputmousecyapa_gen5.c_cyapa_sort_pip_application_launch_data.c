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
typedef  scalar_t__ u8 ;
struct cyapa {int dummy; } ;

/* Variables and functions */
 int PIP_RESP_LENGTH_SIZE ; 

__attribute__((used)) static bool cyapa_sort_pip_application_launch_data(struct cyapa *cyapa,
		u8 *buf, int len)
{
	if (buf == NULL || len < PIP_RESP_LENGTH_SIZE)
		return false;

	/*
	 * After reset or power on, trackpad device always sets to 0x00 0x00
	 * to indicate a reset or power on event.
	 */
	if (buf[0] == 0 && buf[1] == 0)
		return true;

	return false;
}