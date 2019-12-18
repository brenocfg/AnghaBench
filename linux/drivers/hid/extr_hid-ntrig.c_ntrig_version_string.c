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
typedef  int __u8 ;

/* Variables and functions */
 int sprintf (char*,char*,int,int,int,int,int) ; 

__attribute__((used)) static int ntrig_version_string(unsigned char *raw, char *buf)
{
	__u8 a =  (raw[1] & 0x0e) >> 1;
	__u8 b =  (raw[0] & 0x3c) >> 2;
	__u8 c = ((raw[0] & 0x03) << 3) | ((raw[3] & 0xe0) >> 5);
	__u8 d = ((raw[3] & 0x07) << 3) | ((raw[2] & 0xe0) >> 5);
	__u8 e =   raw[2] & 0x07;

	/*
	 * As yet unmapped bits:
	 * 0b11000000 0b11110001 0b00011000 0b00011000
	 */

	return sprintf(buf, "%u.%u.%u.%u.%u", a, b, c, d, e);
}