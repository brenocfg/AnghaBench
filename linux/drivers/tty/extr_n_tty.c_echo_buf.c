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
struct n_tty_data {unsigned char* echo_buf; } ;

/* Variables and functions */
 int N_TTY_BUF_SIZE ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static inline unsigned char echo_buf(struct n_tty_data *ldata, size_t i)
{
	smp_rmb(); /* Matches smp_wmb() in add_echo_byte(). */
	return ldata->echo_buf[i & (N_TTY_BUF_SIZE - 1)];
}