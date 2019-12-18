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
struct adi_port {struct adi* adi; } ;
struct adi {int ret; int* data; scalar_t__ idx; } ;

/* Variables and functions */

__attribute__((used)) static void adi_move_bits(struct adi_port *port, int length)
{
	int i;
	struct adi *adi = port->adi;

	adi[0].idx = adi[1].idx = 0;

	if (adi[0].ret <= 0 || adi[1].ret <= 0) return;
	if (adi[0].data[0] & 0x20 || ~adi[1].data[0] & 0x20) return;

	for (i = 1; i <= adi[1].ret; i++)
		adi[0].data[((length - 1) >> 1) + i + 1] = adi[1].data[i];

	adi[0].ret += adi[1].ret;
	adi[1].ret = -1;
}