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
struct profi_priv {int power_on; struct anybuss_client* client; } ;
struct anybuss_memcfg {int input_io; int output_io; int /*<<< orphan*/  offl_mode; int /*<<< orphan*/  output_total; int /*<<< orphan*/  output_dpram; int /*<<< orphan*/  input_total; int /*<<< orphan*/  input_dpram; } ;
struct anybuss_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB_OFFL_MODE_CLEAR ; 
 int /*<<< orphan*/  PROFI_DPRAM_SIZE ; 
 int anybuss_finish_init (struct anybuss_client*) ; 
 int anybuss_set_power (struct anybuss_client*,int) ; 
 int anybuss_start_init (struct anybuss_client*,struct anybuss_memcfg const*) ; 

__attribute__((used)) static int __profi_enable(struct profi_priv *priv)
{
	int ret;
	struct anybuss_client *client = priv->client;
	/* Initialization Sequence, Generic Anybus Mode */
	const struct anybuss_memcfg mem_cfg = {
		.input_io = 220,
		.input_dpram = PROFI_DPRAM_SIZE,
		.input_total = PROFI_DPRAM_SIZE,
		.output_io = 220,
		.output_dpram = PROFI_DPRAM_SIZE,
		.output_total = PROFI_DPRAM_SIZE,
		.offl_mode = AB_OFFL_MODE_CLEAR,
	};

	/*
	 * switch anybus off then on, this ensures we can do a complete
	 * configuration cycle in case anybus was already on.
	 */
	anybuss_set_power(client, false);
	ret = anybuss_set_power(client, true);
	if (ret)
		goto err;
	ret = anybuss_start_init(client, &mem_cfg);
	if (ret)
		goto err;
	ret = anybuss_finish_init(client);
	if (ret)
		goto err;
	priv->power_on = true;
	return 0;

err:
	anybuss_set_power(client, false);
	priv->power_on = false;
	return ret;
}