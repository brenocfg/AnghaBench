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
struct net_device {int dummy; } ;
struct amd8111e_coalesce_conf {int tx_packets; int tx_prev_packets; int tx_bytes; int tx_prev_bytes; int rx_packets; int rx_prev_packets; int rx_bytes; int rx_prev_bytes; scalar_t__ rx_coal_type; int rx_timeout; int rx_event_count; scalar_t__ tx_coal_type; int tx_timeout; int tx_event_count; } ;
struct amd8111e_priv {struct amd8111e_coalesce_conf coal_conf; } ;

/* Variables and functions */
 scalar_t__ HIGH_COALESCE ; 
 scalar_t__ LOW_COALESCE ; 
 scalar_t__ MEDIUM_COALESCE ; 
 scalar_t__ NO_COALESCE ; 
 int /*<<< orphan*/  RX_INTR_COAL ; 
 int /*<<< orphan*/  TX_INTR_COAL ; 
 int /*<<< orphan*/  amd8111e_set_coalesce (struct net_device*,int /*<<< orphan*/ ) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int amd8111e_calc_coalesce(struct net_device *dev)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	struct amd8111e_coalesce_conf *coal_conf = &lp->coal_conf;
	int tx_pkt_rate;
	int rx_pkt_rate;
	int tx_data_rate;
	int rx_data_rate;
	int rx_pkt_size;
	int tx_pkt_size;

	tx_pkt_rate = coal_conf->tx_packets - coal_conf->tx_prev_packets;
	coal_conf->tx_prev_packets =  coal_conf->tx_packets;

	tx_data_rate = coal_conf->tx_bytes - coal_conf->tx_prev_bytes;
	coal_conf->tx_prev_bytes =  coal_conf->tx_bytes;

	rx_pkt_rate = coal_conf->rx_packets - coal_conf->rx_prev_packets;
	coal_conf->rx_prev_packets =  coal_conf->rx_packets;

	rx_data_rate = coal_conf->rx_bytes - coal_conf->rx_prev_bytes;
	coal_conf->rx_prev_bytes =  coal_conf->rx_bytes;

	if(rx_pkt_rate < 800){
		if(coal_conf->rx_coal_type != NO_COALESCE){

			coal_conf->rx_timeout = 0x0;
			coal_conf->rx_event_count = 0;
			amd8111e_set_coalesce(dev,RX_INTR_COAL);
			coal_conf->rx_coal_type = NO_COALESCE;
		}
	}
	else{

		rx_pkt_size = rx_data_rate/rx_pkt_rate;
		if (rx_pkt_size < 128){
			if(coal_conf->rx_coal_type != NO_COALESCE){

				coal_conf->rx_timeout = 0;
				coal_conf->rx_event_count = 0;
				amd8111e_set_coalesce(dev,RX_INTR_COAL);
				coal_conf->rx_coal_type = NO_COALESCE;
			}

		}
		else if ( (rx_pkt_size >= 128) && (rx_pkt_size < 512) ){

			if(coal_conf->rx_coal_type !=  LOW_COALESCE){
				coal_conf->rx_timeout = 1;
				coal_conf->rx_event_count = 4;
				amd8111e_set_coalesce(dev,RX_INTR_COAL);
				coal_conf->rx_coal_type = LOW_COALESCE;
			}
		}
		else if ((rx_pkt_size >= 512) && (rx_pkt_size < 1024)){

			if(coal_conf->rx_coal_type !=  MEDIUM_COALESCE){
				coal_conf->rx_timeout = 1;
				coal_conf->rx_event_count = 4;
				amd8111e_set_coalesce(dev,RX_INTR_COAL);
				coal_conf->rx_coal_type = MEDIUM_COALESCE;
			}

		}
		else if(rx_pkt_size >= 1024){
			if(coal_conf->rx_coal_type !=  HIGH_COALESCE){
				coal_conf->rx_timeout = 2;
				coal_conf->rx_event_count = 3;
				amd8111e_set_coalesce(dev,RX_INTR_COAL);
				coal_conf->rx_coal_type = HIGH_COALESCE;
			}
		}
	}
    	/* NOW FOR TX INTR COALESC */
	if(tx_pkt_rate < 800){
		if(coal_conf->tx_coal_type != NO_COALESCE){

			coal_conf->tx_timeout = 0x0;
			coal_conf->tx_event_count = 0;
			amd8111e_set_coalesce(dev,TX_INTR_COAL);
			coal_conf->tx_coal_type = NO_COALESCE;
		}
	}
	else{

		tx_pkt_size = tx_data_rate/tx_pkt_rate;
		if (tx_pkt_size < 128){

			if(coal_conf->tx_coal_type != NO_COALESCE){

				coal_conf->tx_timeout = 0;
				coal_conf->tx_event_count = 0;
				amd8111e_set_coalesce(dev,TX_INTR_COAL);
				coal_conf->tx_coal_type = NO_COALESCE;
			}

		}
		else if ( (tx_pkt_size >= 128) && (tx_pkt_size < 512) ){

			if(coal_conf->tx_coal_type !=  LOW_COALESCE){
				coal_conf->tx_timeout = 1;
				coal_conf->tx_event_count = 2;
				amd8111e_set_coalesce(dev,TX_INTR_COAL);
				coal_conf->tx_coal_type = LOW_COALESCE;

			}
		}
		else if ((tx_pkt_size >= 512) && (tx_pkt_size < 1024)){

			if(coal_conf->tx_coal_type !=  MEDIUM_COALESCE){
				coal_conf->tx_timeout = 2;
				coal_conf->tx_event_count = 5;
				amd8111e_set_coalesce(dev,TX_INTR_COAL);
				coal_conf->tx_coal_type = MEDIUM_COALESCE;
			}
		} else if (tx_pkt_size >= 1024) {
			if (coal_conf->tx_coal_type != HIGH_COALESCE) {
				coal_conf->tx_timeout = 4;
				coal_conf->tx_event_count = 8;
				amd8111e_set_coalesce(dev, TX_INTR_COAL);
				coal_conf->tx_coal_type = HIGH_COALESCE;
			}
		}
	}
	return 0;

}