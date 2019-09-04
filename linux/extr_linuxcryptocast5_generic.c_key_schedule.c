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
typedef  int u32 ;

/* Variables and functions */
 int* s5 ; 
 int* s6 ; 
 int* s7 ; 
 int* sb8 ; 

__attribute__((used)) static void key_schedule(u32 *x, u32 *z, u32 *k)
{

#define xi(i)   ((x[(i)/4] >> (8*(3-((i)%4)))) & 0xff)
#define zi(i)   ((z[(i)/4] >> (8*(3-((i)%4)))) & 0xff)

	z[0] = x[0] ^ s5[xi(13)] ^ s6[xi(15)] ^ s7[xi(12)] ^ sb8[xi(14)] ^
	    s7[xi(8)];
	z[1] = x[2] ^ s5[zi(0)] ^ s6[zi(2)] ^ s7[zi(1)] ^ sb8[zi(3)] ^
	    sb8[xi(10)];
	z[2] = x[3] ^ s5[zi(7)] ^ s6[zi(6)] ^ s7[zi(5)] ^ sb8[zi(4)] ^
	    s5[xi(9)];
	z[3] = x[1] ^ s5[zi(10)] ^ s6[zi(9)] ^ s7[zi(11)] ^ sb8[zi(8)] ^
	    s6[xi(11)];
	k[0] = s5[zi(8)] ^ s6[zi(9)] ^ s7[zi(7)] ^ sb8[zi(6)] ^ s5[zi(2)];
	k[1] = s5[zi(10)] ^ s6[zi(11)] ^ s7[zi(5)] ^ sb8[zi(4)] ^
	    s6[zi(6)];
	k[2] = s5[zi(12)] ^ s6[zi(13)] ^ s7[zi(3)] ^ sb8[zi(2)] ^
	    s7[zi(9)];
	k[3] = s5[zi(14)] ^ s6[zi(15)] ^ s7[zi(1)] ^ sb8[zi(0)] ^
	    sb8[zi(12)];

	x[0] = z[2] ^ s5[zi(5)] ^ s6[zi(7)] ^ s7[zi(4)] ^ sb8[zi(6)] ^
	    s7[zi(0)];
	x[1] = z[0] ^ s5[xi(0)] ^ s6[xi(2)] ^ s7[xi(1)] ^ sb8[xi(3)] ^
	    sb8[zi(2)];
	x[2] = z[1] ^ s5[xi(7)] ^ s6[xi(6)] ^ s7[xi(5)] ^ sb8[xi(4)] ^
	    s5[zi(1)];
	x[3] = z[3] ^ s5[xi(10)] ^ s6[xi(9)] ^ s7[xi(11)] ^ sb8[xi(8)] ^
	    s6[zi(3)];
	k[4] = s5[xi(3)] ^ s6[xi(2)] ^ s7[xi(12)] ^ sb8[xi(13)] ^
	    s5[xi(8)];
	k[5] = s5[xi(1)] ^ s6[xi(0)] ^ s7[xi(14)] ^ sb8[xi(15)] ^
	    s6[xi(13)];
	k[6] = s5[xi(7)] ^ s6[xi(6)] ^ s7[xi(8)] ^ sb8[xi(9)] ^ s7[xi(3)];
	k[7] = s5[xi(5)] ^ s6[xi(4)] ^ s7[xi(10)] ^ sb8[xi(11)] ^
	    sb8[xi(7)];

	z[0] = x[0] ^ s5[xi(13)] ^ s6[xi(15)] ^ s7[xi(12)] ^ sb8[xi(14)] ^
	    s7[xi(8)];
	z[1] = x[2] ^ s5[zi(0)] ^ s6[zi(2)] ^ s7[zi(1)] ^ sb8[zi(3)] ^
	    sb8[xi(10)];
	z[2] = x[3] ^ s5[zi(7)] ^ s6[zi(6)] ^ s7[zi(5)] ^ sb8[zi(4)] ^
	    s5[xi(9)];
	z[3] = x[1] ^ s5[zi(10)] ^ s6[zi(9)] ^ s7[zi(11)] ^ sb8[zi(8)] ^
	    s6[xi(11)];
	k[8] = s5[zi(3)] ^ s6[zi(2)] ^ s7[zi(12)] ^ sb8[zi(13)] ^
	    s5[zi(9)];
	k[9] = s5[zi(1)] ^ s6[zi(0)] ^ s7[zi(14)] ^ sb8[zi(15)] ^
	    s6[zi(12)];
	k[10] = s5[zi(7)] ^ s6[zi(6)] ^ s7[zi(8)] ^ sb8[zi(9)] ^ s7[zi(2)];
	k[11] = s5[zi(5)] ^ s6[zi(4)] ^ s7[zi(10)] ^ sb8[zi(11)] ^
	    sb8[zi(6)];

	x[0] = z[2] ^ s5[zi(5)] ^ s6[zi(7)] ^ s7[zi(4)] ^ sb8[zi(6)] ^
	    s7[zi(0)];
	x[1] = z[0] ^ s5[xi(0)] ^ s6[xi(2)] ^ s7[xi(1)] ^ sb8[xi(3)] ^
	    sb8[zi(2)];
	x[2] = z[1] ^ s5[xi(7)] ^ s6[xi(6)] ^ s7[xi(5)] ^ sb8[xi(4)] ^
	    s5[zi(1)];
	x[3] = z[3] ^ s5[xi(10)] ^ s6[xi(9)] ^ s7[xi(11)] ^ sb8[xi(8)] ^
	    s6[zi(3)];
	k[12] = s5[xi(8)] ^ s6[xi(9)] ^ s7[xi(7)] ^ sb8[xi(6)] ^ s5[xi(3)];
	k[13] = s5[xi(10)] ^ s6[xi(11)] ^ s7[xi(5)] ^ sb8[xi(4)] ^
	    s6[xi(7)];
	k[14] = s5[xi(12)] ^ s6[xi(13)] ^ s7[xi(3)] ^ sb8[xi(2)] ^
	    s7[xi(8)];
	k[15] = s5[xi(14)] ^ s6[xi(15)] ^ s7[xi(1)] ^ sb8[xi(0)] ^
	    sb8[xi(13)];

#undef xi
#undef zi
}