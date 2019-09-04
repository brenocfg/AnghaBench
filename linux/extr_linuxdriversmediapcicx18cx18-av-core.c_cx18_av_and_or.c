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
typedef  unsigned int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 unsigned int cx18_av_read (struct cx18*,int /*<<< orphan*/ ) ; 
 int cx18_av_write (struct cx18*,int /*<<< orphan*/ ,unsigned int) ; 

int cx18_av_and_or(struct cx18 *cx, u16 addr, unsigned and_mask,
		   u8 or_value)
{
	return cx18_av_write(cx, addr,
			     (cx18_av_read(cx, addr) & and_mask) |
			     or_value);
}