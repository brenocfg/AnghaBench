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
struct mvneta_rx_queue {int dummy; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvneta_rxq_hw_init (struct mvneta_port*,struct mvneta_rx_queue*) ; 
 int mvneta_rxq_sw_init (struct mvneta_port*,struct mvneta_rx_queue*) ; 

__attribute__((used)) static int mvneta_rxq_init(struct mvneta_port *pp,
			   struct mvneta_rx_queue *rxq)

{
	int ret;

	ret = mvneta_rxq_sw_init(pp, rxq);
	if (ret < 0)
		return ret;

	mvneta_rxq_hw_init(pp, rxq);

	return 0;
}