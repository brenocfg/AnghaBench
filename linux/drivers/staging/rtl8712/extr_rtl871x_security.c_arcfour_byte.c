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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct arc4context {size_t* state; int x; size_t y; } ;

/* Variables and functions */

__attribute__((used)) static u32 arcfour_byte(struct arc4context *parc4ctx)
{
	u32 x;
	u32 y;
	u32 sx, sy;
	u8 *state;

	state = parc4ctx->state;
	x = (parc4ctx->x + 1) & 0xff;
	sx = state[x];
	y = (sx + parc4ctx->y) & 0xff;
	sy = state[y];
	parc4ctx->x = x;
	parc4ctx->y = y;
	state[y] = (u8)sx;
	state[x] = (u8)sy;
	return state[(sx + sy) & 0xff];
}