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
struct wl1251_acx_mem_map {int /*<<< orphan*/  rx_control_addr; int /*<<< orphan*/  num_rx_mem_blocks; int /*<<< orphan*/  tx_control_addr; int /*<<< orphan*/  num_tx_mem_blocks; } ;
struct wl1251 {struct wl1251_acx_mem_map* target_mem_map; struct wl1251_acx_mem_map* data_path; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int RX_CFG_PROMISCUOUS ; 
 int RX_CFG_TSF ; 
 int /*<<< orphan*/  RX_FILTER_OPTION_DEF ; 
 int /*<<< orphan*/  kfree (struct wl1251_acx_mem_map*) ; 
 int wl1251_acx_conn_monit_params (struct wl1251*) ; 
 int wl1251_cmd_data_path_rx (struct wl1251*,int /*<<< orphan*/ ,int) ; 
 int wl1251_cmd_data_path_tx (struct wl1251*,int /*<<< orphan*/ ,int) ; 
 int wl1251_hw_init_beacon_broadcast (struct wl1251*) ; 
 int wl1251_hw_init_beacon_filter (struct wl1251*) ; 
 int wl1251_hw_init_data_path_config (struct wl1251*) ; 
 int wl1251_hw_init_energy_detection (struct wl1251*) ; 
 int wl1251_hw_init_hwenc_config (struct wl1251*) ; 
 int wl1251_hw_init_mem_config (struct wl1251*) ; 
 int wl1251_hw_init_phy_config (struct wl1251*) ; 
 int wl1251_hw_init_power_auth (struct wl1251*) ; 
 int wl1251_hw_init_pta (struct wl1251*) ; 
 int wl1251_hw_init_rx_config (struct wl1251*,int,int /*<<< orphan*/ ) ; 
 int wl1251_hw_init_templates_config (struct wl1251*) ; 
 int wl1251_hw_init_tx_queue_config (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wl1251_hw_init(struct wl1251 *wl)
{
	struct wl1251_acx_mem_map *wl_mem_map;
	int ret;

	ret = wl1251_hw_init_hwenc_config(wl);
	if (ret < 0)
		return ret;

	/* Template settings */
	ret = wl1251_hw_init_templates_config(wl);
	if (ret < 0)
		return ret;

	/* Default memory configuration */
	ret = wl1251_hw_init_mem_config(wl);
	if (ret < 0)
		return ret;

	/* Default data path configuration  */
	ret = wl1251_hw_init_data_path_config(wl);
	if (ret < 0)
		goto out_free_memmap;

	/* RX config */
	ret = wl1251_hw_init_rx_config(wl,
				       RX_CFG_PROMISCUOUS | RX_CFG_TSF,
				       RX_FILTER_OPTION_DEF);
	/* RX_CONFIG_OPTION_ANY_DST_ANY_BSS,
	   RX_FILTER_OPTION_FILTER_ALL); */
	if (ret < 0)
		goto out_free_data_path;

	/* TX queues config */
	ret = wl1251_hw_init_tx_queue_config(wl);
	if (ret < 0)
		goto out_free_data_path;

	/* PHY layer config */
	ret = wl1251_hw_init_phy_config(wl);
	if (ret < 0)
		goto out_free_data_path;

	/* Initialize connection monitoring thresholds */
	ret = wl1251_acx_conn_monit_params(wl);
	if (ret < 0)
		goto out_free_data_path;

	/* Beacon filtering */
	ret = wl1251_hw_init_beacon_filter(wl);
	if (ret < 0)
		goto out_free_data_path;

	/* Bluetooth WLAN coexistence */
	ret = wl1251_hw_init_pta(wl);
	if (ret < 0)
		goto out_free_data_path;

	/* Energy detection */
	ret = wl1251_hw_init_energy_detection(wl);
	if (ret < 0)
		goto out_free_data_path;

	/* Beacons and boradcast settings */
	ret = wl1251_hw_init_beacon_broadcast(wl);
	if (ret < 0)
		goto out_free_data_path;

	/* Enable rx data path */
	ret = wl1251_cmd_data_path_rx(wl, wl->channel, 1);
	if (ret < 0)
		goto out_free_data_path;

	/* Enable tx data path */
	ret = wl1251_cmd_data_path_tx(wl, wl->channel, 1);
	if (ret < 0)
		goto out_free_data_path;

	/* Default power state */
	ret = wl1251_hw_init_power_auth(wl);
	if (ret < 0)
		goto out_free_data_path;

	wl_mem_map = wl->target_mem_map;
	wl1251_info("%d tx blocks at 0x%x, %d rx blocks at 0x%x",
		    wl_mem_map->num_tx_mem_blocks,
		    wl->data_path->tx_control_addr,
		    wl_mem_map->num_rx_mem_blocks,
		    wl->data_path->rx_control_addr);

	return 0;

 out_free_data_path:
	kfree(wl->data_path);

 out_free_memmap:
	kfree(wl->target_mem_map);

	return ret;
}