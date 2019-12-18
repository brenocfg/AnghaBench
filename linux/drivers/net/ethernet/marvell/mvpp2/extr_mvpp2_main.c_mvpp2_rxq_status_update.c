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
struct mvpp2_port {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int MVPP2_RXQ_NUM_NEW_OFFSET ; 
 int /*<<< orphan*/  MVPP2_RXQ_STATUS_UPDATE_REG (int) ; 
 int /*<<< orphan*/  mvpp2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
mvpp2_rxq_status_update(struct mvpp2_port *port, int rxq_id,
			int used_count, int free_count)
{
	/* Decrement the number of used descriptors and increment count
	 * increment the number of free descriptors.
	 */
	u32 val = used_count | (free_count << MVPP2_RXQ_NUM_NEW_OFFSET);

	mvpp2_write(port->priv, MVPP2_RXQ_STATUS_UPDATE_REG(rxq_id), val);
}