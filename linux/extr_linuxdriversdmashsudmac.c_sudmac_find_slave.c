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
struct sudmac_slave_config {int slave_id; } ;
struct sudmac_pdata {int slave_num; struct sudmac_slave_config* slave; } ;
struct sudmac_device {struct sudmac_pdata* pdata; } ;
struct sudmac_chan {int dummy; } ;

/* Variables and functions */
 struct sudmac_device* to_sdev (struct sudmac_chan*) ; 

__attribute__((used)) static const struct sudmac_slave_config *sudmac_find_slave(
	struct sudmac_chan *sc, int slave_id)
{
	struct sudmac_device *sdev = to_sdev(sc);
	struct sudmac_pdata *pdata = sdev->pdata;
	const struct sudmac_slave_config *cfg;
	int i;

	for (i = 0, cfg = pdata->slave; i < pdata->slave_num; i++, cfg++)
		if (cfg->slave_id == slave_id)
			return cfg;

	return NULL;
}