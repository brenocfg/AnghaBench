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
struct mvpp2_port {int nrxqs; int first_rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online (int) ; 
 int num_possible_cpus () ; 

__attribute__((used)) static inline u32 mvpp22_rxfh_indir(struct mvpp2_port *port, u32 rxq)
{
	int nrxqs, cpu, cpus = num_possible_cpus();

	/* Number of RXQs per CPU */
	nrxqs = port->nrxqs / cpus;

	/* CPU that will handle this rx queue */
	cpu = rxq / nrxqs;

	if (!cpu_online(cpu))
		return port->first_rxq;

	/* Indirection to better distribute the paquets on the CPUs when
	 * configuring the RSS queues.
	 */
	return port->first_rxq + ((rxq * nrxqs + rxq / cpus) % port->nrxqs);
}