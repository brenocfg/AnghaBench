#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mac_device {TYPE_1__* priv; int /*<<< orphan*/  adjust_link; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  set_multi; int /*<<< orphan*/  set_tstamp; int /*<<< orphan*/  set_allmulti; int /*<<< orphan*/  set_exception; int /*<<< orphan*/  set_rx_pause; int /*<<< orphan*/  set_tx_pause; int /*<<< orphan*/  remove_hash_mac_addr; int /*<<< orphan*/  add_hash_mac_addr; int /*<<< orphan*/  change_addr; int /*<<< orphan*/  set_promisc; int /*<<< orphan*/  init; } ;
struct TYPE_2__ {int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_link_void ; 
 int /*<<< orphan*/  set_multi ; 
 int /*<<< orphan*/  start ; 
 int /*<<< orphan*/  stop ; 
 int /*<<< orphan*/  tgec_accept_rx_pause_frames ; 
 int /*<<< orphan*/  tgec_add_hash_mac_address ; 
 int /*<<< orphan*/  tgec_del_hash_mac_address ; 
 int /*<<< orphan*/  tgec_disable ; 
 int /*<<< orphan*/  tgec_enable ; 
 int /*<<< orphan*/  tgec_initialization ; 
 int /*<<< orphan*/  tgec_modify_mac_address ; 
 int /*<<< orphan*/  tgec_set_allmulti ; 
 int /*<<< orphan*/  tgec_set_exception ; 
 int /*<<< orphan*/  tgec_set_promiscuous ; 
 int /*<<< orphan*/  tgec_set_tstamp ; 
 int /*<<< orphan*/  tgec_set_tx_pause_frames ; 

__attribute__((used)) static void setup_tgec(struct mac_device *mac_dev)
{
	mac_dev->init			= tgec_initialization;
	mac_dev->set_promisc		= tgec_set_promiscuous;
	mac_dev->change_addr		= tgec_modify_mac_address;
	mac_dev->add_hash_mac_addr	= tgec_add_hash_mac_address;
	mac_dev->remove_hash_mac_addr	= tgec_del_hash_mac_address;
	mac_dev->set_tx_pause		= tgec_set_tx_pause_frames;
	mac_dev->set_rx_pause		= tgec_accept_rx_pause_frames;
	mac_dev->set_exception		= tgec_set_exception;
	mac_dev->set_allmulti		= tgec_set_allmulti;
	mac_dev->set_tstamp		= tgec_set_tstamp;
	mac_dev->set_multi		= set_multi;
	mac_dev->start			= start;
	mac_dev->stop			= stop;
	mac_dev->adjust_link            = adjust_link_void;
	mac_dev->priv->enable		= tgec_enable;
	mac_dev->priv->disable		= tgec_disable;
}