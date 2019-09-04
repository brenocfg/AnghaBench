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
typedef  int /*<<< orphan*/  optval ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_QDISC_BYPASS ; 
 int /*<<< orphan*/  SOL_PACKET ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

bool uml_raw_enable_qdisc_bypass(int fd)
{
	int optval = 1;

	if (setsockopt(fd,
		SOL_PACKET, PACKET_QDISC_BYPASS,
		&optval, sizeof(optval)) != 0) {
		return false;
	}
	return true;
}