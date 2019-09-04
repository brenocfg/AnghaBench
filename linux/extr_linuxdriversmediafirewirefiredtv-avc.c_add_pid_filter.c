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
struct firedtv {int* channel_pid; int /*<<< orphan*/  channel_active; } ;

/* Variables and functions */
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_pid_filter(struct firedtv *fdtv, u8 *operand)
{
	int i, n, pos = 1;

	for (i = 0, n = 0; i < 16; i++) {
		if (test_bit(i, &fdtv->channel_active)) {
			operand[pos++] = 0x13; /* flowfunction relay */
			operand[pos++] = 0x80; /* dsd_sel_spec_valid_flags -> PID */
			operand[pos++] = (fdtv->channel_pid[i] >> 8) & 0x1f;
			operand[pos++] = fdtv->channel_pid[i] & 0xff;
			operand[pos++] = 0x00; /* tableID */
			operand[pos++] = 0x00; /* filter_length */
			n++;
		}
	}
	operand[0] = n;

	return pos;
}