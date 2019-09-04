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
typedef  int /*<<< orphan*/  u16 ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int cx18_av_read4 (struct cx18*,int /*<<< orphan*/ ) ; 
 int cx18_av_write4 (struct cx18*,int /*<<< orphan*/ ,int) ; 

int cx18_av_and_or4(struct cx18 *cx, u16 addr, u32 and_mask,
		   u32 or_value)
{
	return cx18_av_write4(cx, addr,
			     (cx18_av_read4(cx, addr) & and_mask) |
			     or_value);
}