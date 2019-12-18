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
struct n_tty_data {int /*<<< orphan*/  echo_head; } ;

/* Variables and functions */
 unsigned char* echo_buf_addr (struct n_tty_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static inline void add_echo_byte(unsigned char c, struct n_tty_data *ldata)
{
	*echo_buf_addr(ldata, ldata->echo_head) = c;
	smp_wmb(); /* Matches smp_rmb() in echo_buf(). */
	ldata->echo_head++;
}