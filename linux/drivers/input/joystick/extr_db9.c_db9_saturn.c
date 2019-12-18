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
struct parport {int dummy; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  n_pads; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB9_MAX_DEVICES ; 
#define  DB9_SATURN_DPP 130 
#define  DB9_SATURN_DPP_2 129 
#define  DB9_SATURN_PAD 128 
 TYPE_1__* db9_modes ; 
 unsigned char db9_saturn_read_packet (struct parport*,unsigned char*,int,int) ; 
 int db9_saturn_report (unsigned char,unsigned char*,struct input_dev**,int,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db9_saturn(int mode, struct parport *port, struct input_dev *devs[])
{
	unsigned char id, data[60];
	int type, n, max_pads;
	int tmp, i;

	switch (mode) {
	case DB9_SATURN_PAD:
		type = 0;
		n = 1;
		break;
	case DB9_SATURN_DPP:
		type = 1;
		n = 1;
		break;
	case DB9_SATURN_DPP_2:
		type = 1;
		n = 2;
		break;
	default:
		return -1;
	}
	max_pads = min(db9_modes[mode].n_pads, DB9_MAX_DEVICES);
	for (tmp = 0, i = 0; i < n; i++) {
		id = db9_saturn_read_packet(port, data, type + i, 1);
		tmp = db9_saturn_report(id, data, devs, tmp, max_pads);
	}
	return 0;
}