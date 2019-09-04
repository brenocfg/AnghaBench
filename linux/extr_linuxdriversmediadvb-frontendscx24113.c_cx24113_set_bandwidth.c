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
typedef  int u32 ;
struct cx24113_state {int dummy; } ;

/* Variables and functions */
 int cx24113_writereg (struct cx24113_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 

__attribute__((used)) static int cx24113_set_bandwidth(struct cx24113_state *state, u32 bandwidth_khz)
{
	u8 r;

	if (bandwidth_khz <= 19000)
		r = 0x03 << 6;
	else if (bandwidth_khz <= 25000)
		r = 0x02 << 6;
	else
		r = 0x01 << 6;

	dprintk("bandwidth to be set: %d\n", bandwidth_khz);
	bandwidth_khz *= 10;
	bandwidth_khz -= 10000;
	bandwidth_khz /= 1000;
	bandwidth_khz += 5;
	bandwidth_khz /= 10;

	dprintk("bandwidth: %d %d\n", r >> 6, bandwidth_khz);

	r |= bandwidth_khz & 0x3f;

	return cx24113_writereg(state, 0x1e, r);
}