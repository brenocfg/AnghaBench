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
struct i2400m {size_t tx_in; } ;

/* Variables and functions */
 size_t I2400M_TX_BUF_SIZE ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline
size_t __i2400m_tx_tail_room(struct i2400m *i2400m)
{
	size_t tail_room;
	size_t tx_in;

	if (unlikely(i2400m->tx_in == 0))
		return I2400M_TX_BUF_SIZE;
	tx_in = i2400m->tx_in % I2400M_TX_BUF_SIZE;
	tail_room = I2400M_TX_BUF_SIZE - tx_in;
	tail_room %= I2400M_TX_BUF_SIZE;
	return tail_room;
}