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
struct sudmac_slave_config {int dummy; } ;
struct sudmac_chan {int dummy; } ;
struct shdma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENODEV ; 
 struct sudmac_slave_config* sudmac_find_slave (struct sudmac_chan*,int) ; 
 struct sudmac_chan* to_chan (struct shdma_chan*) ; 

__attribute__((used)) static int sudmac_set_slave(struct shdma_chan *schan, int slave_id,
			    dma_addr_t slave_addr, bool try)
{
	struct sudmac_chan *sc = to_chan(schan);
	const struct sudmac_slave_config *cfg = sudmac_find_slave(sc, slave_id);

	if (!cfg)
		return -ENODEV;

	return 0;
}