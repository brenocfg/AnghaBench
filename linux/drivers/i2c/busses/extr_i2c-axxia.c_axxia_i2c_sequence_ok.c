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
struct i2c_msg {scalar_t__ len; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ FIFO_SIZE ; 
 int SEQ_LEN ; 
 scalar_t__ i2c_m_rd (struct i2c_msg*) ; 

__attribute__((used)) static bool axxia_i2c_sequence_ok(struct i2c_msg msgs[], int num)
{
	return num == SEQ_LEN && !i2c_m_rd(&msgs[0]) && i2c_m_rd(&msgs[1]) &&
	       msgs[0].len > 0 && msgs[0].len <= FIFO_SIZE &&
	       msgs[1].len > 0 && msgs[0].addr == msgs[1].addr;
}