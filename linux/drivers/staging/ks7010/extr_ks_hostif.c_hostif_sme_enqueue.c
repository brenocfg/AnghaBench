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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {size_t qtail; int /*<<< orphan*/ * event_buff; } ;
struct ks_wlan_private {int /*<<< orphan*/  sme_task; int /*<<< orphan*/  net_dev; TYPE_1__ sme_i; } ;

/* Variables and functions */
 int SME_EVENT_BUFF_SIZE ; 
 int cnt_smeqbody (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  inc_smeqtail (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void hostif_sme_enqueue(struct ks_wlan_private *priv, u16 event)
{
	/* enqueue sme event */
	if (cnt_smeqbody(priv) < (SME_EVENT_BUFF_SIZE - 1)) {
		priv->sme_i.event_buff[priv->sme_i.qtail] = event;
		inc_smeqtail(priv);
	} else {
		/* in case of buffer overflow */
		netdev_err(priv->net_dev, "sme queue buffer overflow\n");
	}

	tasklet_schedule(&priv->sme_task);
}