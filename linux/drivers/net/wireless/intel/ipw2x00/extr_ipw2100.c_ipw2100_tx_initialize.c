#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int available; int entries; scalar_t__ next; scalar_t__ oldest; } ;
struct ipw2100_priv {TYPE_4__ tx_queue; int /*<<< orphan*/  txq_stat; int /*<<< orphan*/  tx_free_stat; int /*<<< orphan*/  tx_free_list; TYPE_3__* tx_buffers; int /*<<< orphan*/  tx_pend_stat; int /*<<< orphan*/  tx_pend_list; int /*<<< orphan*/  fw_pend_stat; int /*<<< orphan*/  fw_pend_list; } ;
struct TYPE_5__ {int /*<<< orphan*/ * txb; } ;
struct TYPE_6__ {TYPE_1__ d_struct; } ;
struct TYPE_7__ {int /*<<< orphan*/  list; TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_STAT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IPW_MEM_HOST_SHARED_TX_QUEUE_BD_BASE ; 
 int /*<<< orphan*/  IPW_MEM_HOST_SHARED_TX_QUEUE_BD_SIZE ; 
 int /*<<< orphan*/  IPW_MEM_HOST_SHARED_TX_QUEUE_READ_INDEX ; 
 int /*<<< orphan*/  IPW_MEM_HOST_SHARED_TX_QUEUE_WRITE_INDEX ; 
 int /*<<< orphan*/  SET_STAT (int /*<<< orphan*/ *,int) ; 
 int TX_PENDED_QUEUE_LENGTH ; 
 int /*<<< orphan*/  bd_queue_initialize (struct ipw2100_priv*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libipw_txb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipw2100_tx_initialize(struct ipw2100_priv *priv)
{
	int i;

	IPW_DEBUG_INFO("enter\n");

	/*
	 * reinitialize packet info lists
	 */
	INIT_LIST_HEAD(&priv->fw_pend_list);
	INIT_STAT(&priv->fw_pend_stat);

	/*
	 * reinitialize lists
	 */
	INIT_LIST_HEAD(&priv->tx_pend_list);
	INIT_LIST_HEAD(&priv->tx_free_list);
	INIT_STAT(&priv->tx_pend_stat);
	INIT_STAT(&priv->tx_free_stat);

	for (i = 0; i < TX_PENDED_QUEUE_LENGTH; i++) {
		/* We simply drop any SKBs that have been queued for
		 * transmit */
		if (priv->tx_buffers[i].info.d_struct.txb) {
			libipw_txb_free(priv->tx_buffers[i].info.d_struct.
					   txb);
			priv->tx_buffers[i].info.d_struct.txb = NULL;
		}

		list_add_tail(&priv->tx_buffers[i].list, &priv->tx_free_list);
	}

	SET_STAT(&priv->tx_free_stat, i);

	priv->tx_queue.oldest = 0;
	priv->tx_queue.available = priv->tx_queue.entries;
	priv->tx_queue.next = 0;
	INIT_STAT(&priv->txq_stat);
	SET_STAT(&priv->txq_stat, priv->tx_queue.available);

	bd_queue_initialize(priv, &priv->tx_queue,
			    IPW_MEM_HOST_SHARED_TX_QUEUE_BD_BASE,
			    IPW_MEM_HOST_SHARED_TX_QUEUE_BD_SIZE,
			    IPW_MEM_HOST_SHARED_TX_QUEUE_READ_INDEX,
			    IPW_MEM_HOST_SHARED_TX_QUEUE_WRITE_INDEX);

	IPW_DEBUG_INFO("exit\n");

}