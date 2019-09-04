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

/* Variables and functions */

__attribute__((used)) static void init_mtus(unsigned short mtus[])
{
	/*
	 * See draft-mathis-plpmtud-00.txt for the values.  The min is 88 so
	 * it can accommodate max size TCP/IP headers when SACK and timestamps
	 * are enabled and still have at least 8 bytes of payload.
	 */
	mtus[0] = 88;
	mtus[1] = 88;
	mtus[2] = 256;
	mtus[3] = 512;
	mtus[4] = 576;
	mtus[5] = 1024;
	mtus[6] = 1280;
	mtus[7] = 1492;
	mtus[8] = 1500;
	mtus[9] = 2002;
	mtus[10] = 2048;
	mtus[11] = 4096;
	mtus[12] = 4352;
	mtus[13] = 8192;
	mtus[14] = 9000;
	mtus[15] = 9600;
}