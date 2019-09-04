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
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static int stv0367ter_duration(s32 mode, int tempo1, int tempo2, int tempo3)
{
	int local_tempo = 0;
	switch (mode) {
	case 0:
		local_tempo = tempo1;
		break;
	case 1:
		local_tempo = tempo2;
		break ;

	case 2:
		local_tempo = tempo3;
		break;

	default:
		break;
	}
	/*	msleep(local_tempo);  */
	return local_tempo;
}