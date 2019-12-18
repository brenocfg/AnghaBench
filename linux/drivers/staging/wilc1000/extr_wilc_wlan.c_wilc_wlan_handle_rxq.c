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
typedef  int /*<<< orphan*/  u8 ;
struct wilc {int /*<<< orphan*/  cfg_event; scalar_t__ quit; } ;
struct rxq_entry_t {int buffer_size; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rxq_entry_t*) ; 
 int /*<<< orphan*/  wilc_wlan_handle_rx_buff (struct wilc*,int /*<<< orphan*/ *,int) ; 
 struct rxq_entry_t* wilc_wlan_rxq_remove (struct wilc*) ; 

__attribute__((used)) static void wilc_wlan_handle_rxq(struct wilc *wilc)
{
	int size;
	u8 *buffer;
	struct rxq_entry_t *rqe;

	do {
		if (wilc->quit) {
			complete(&wilc->cfg_event);
			break;
		}
		rqe = wilc_wlan_rxq_remove(wilc);
		if (!rqe)
			break;

		buffer = rqe->buffer;
		size = rqe->buffer_size;
		wilc_wlan_handle_rx_buff(wilc, buffer, size);

		kfree(rqe);
	} while (1);
}