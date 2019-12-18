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
struct i2400m_msg_hdr {size_t size; } ;
struct i2400m {size_t tx_in; struct i2400m_msg_hdr* tx_buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t I2400M_TX_BUF_SIZE ; 
 size_t I2400M_TX_SKIP ; 
 size_t __i2400m_tx_tail_room (struct i2400m*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,size_t,size_t) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static
void i2400m_tx_skip_tail(struct i2400m *i2400m)
{
	struct device *dev = i2400m_dev(i2400m);
	size_t tx_in = i2400m->tx_in % I2400M_TX_BUF_SIZE;
	size_t tail_room = __i2400m_tx_tail_room(i2400m);
	struct i2400m_msg_hdr *msg = i2400m->tx_buf + tx_in;
	if (unlikely(tail_room == 0))
		return;
	BUG_ON(tail_room < sizeof(*msg));
	msg->size = tail_room | I2400M_TX_SKIP;
	d_printf(2, dev, "skip tail: skipping %zu bytes @%zu\n",
		 tail_room, tx_in);
	i2400m->tx_in += tail_room;
}