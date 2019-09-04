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
struct cdns_i2c {scalar_t__ curr_recv_count; } ;

/* Variables and functions */
 scalar_t__ CDNS_I2C_FIFO_DEPTH ; 

__attribute__((used)) static inline bool cdns_is_holdquirk(struct cdns_i2c *id, bool hold_wrkaround)
{
	return (hold_wrkaround &&
		(id->curr_recv_count == CDNS_I2C_FIFO_DEPTH + 1));
}