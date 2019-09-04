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
typedef  int u16 ;
typedef  unsigned char* _cstruct ;

/* Variables and functions */

__attribute__((used)) static _cstruct b1config_async_v110(u16 rate)
{
	/* CAPI-Spec "B1 Configuration" */
	static unsigned char buf[9];
	buf[0] = 8; /* len */
	/* maximum bitrate */
	buf[1] = rate & 0xff; buf[2] = (rate >> 8) & 0xff;
	buf[3] = 8; buf[4] = 0; /* 8 bits per character */
	buf[5] = 0; buf[6] = 0; /* parity none */
	buf[7] = 0; buf[8] = 0; /* 1 stop bit */
	return buf;
}