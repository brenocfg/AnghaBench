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
typedef  int sint ;

/* Variables and functions */

__attribute__((used)) static void construct_mic_header1(u8 *mic_header1, sint header_length, u8 *mpdu)
{
	mic_header1[0] = (u8)((header_length - 2) / 256);
	mic_header1[1] = (u8)((header_length - 2) % 256);
	mic_header1[2] = mpdu[0] & 0xcf;    /* Mute CF poll & CF ack bits */
	/* Mute retry, more data and pwr mgt bits */
	mic_header1[3] = mpdu[1] & 0xc7;
	mic_header1[4] = mpdu[4];       /* A1 */
	mic_header1[5] = mpdu[5];
	mic_header1[6] = mpdu[6];
	mic_header1[7] = mpdu[7];
	mic_header1[8] = mpdu[8];
	mic_header1[9] = mpdu[9];
	mic_header1[10] = mpdu[10];     /* A2 */
	mic_header1[11] = mpdu[11];
	mic_header1[12] = mpdu[12];
	mic_header1[13] = mpdu[13];
	mic_header1[14] = mpdu[14];
	mic_header1[15] = mpdu[15];
}