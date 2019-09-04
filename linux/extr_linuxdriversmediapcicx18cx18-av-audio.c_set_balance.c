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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx18_av_and_or (struct cx18*,int,int,int) ; 

__attribute__((used)) static void set_balance(struct cx18 *cx, int balance)
{
	int bal = balance >> 8;
	if (bal > 0x80) {
		/* PATH1_BAL_LEFT */
		cx18_av_and_or(cx, 0x8d5, 0x7f, 0x80);
		/* PATH1_BAL_LEVEL */
		cx18_av_and_or(cx, 0x8d5, ~0x7f, bal & 0x7f);
	} else {
		/* PATH1_BAL_LEFT */
		cx18_av_and_or(cx, 0x8d5, 0x7f, 0x00);
		/* PATH1_BAL_LEVEL */
		cx18_av_and_or(cx, 0x8d5, ~0x7f, 0x80 - bal);
	}
}