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
struct mvpp2 {scalar_t__ hw_version; } ;

/* Variables and functions */
 scalar_t__ MVPP22 ; 
 unsigned int MVPP2_PORT_MAX_RXQ ; 
 scalar_t__ MVPP2_QDIST_SINGLE_MODE ; 
 int num_possible_cpus () ; 
 scalar_t__ queue_mode ; 

__attribute__((used)) static int mvpp2_get_nrxqs(struct mvpp2 *priv)
{
	unsigned int nrxqs;

	if (priv->hw_version == MVPP22 && queue_mode == MVPP2_QDIST_SINGLE_MODE)
		return 1;

	/* According to the PPv2.2 datasheet and our experiments on
	 * PPv2.1, RX queues have an allocation granularity of 4 (when
	 * more than a single one on PPv2.2).
	 * Round up to nearest multiple of 4.
	 */
	nrxqs = (num_possible_cpus() + 3) & ~0x3;
	if (nrxqs > MVPP2_PORT_MAX_RXQ)
		nrxqs = MVPP2_PORT_MAX_RXQ;

	return nrxqs;
}