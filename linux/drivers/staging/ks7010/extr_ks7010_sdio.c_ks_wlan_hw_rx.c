#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
struct rx_device_buffer {void* size; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {int /*<<< orphan*/  confirm_wait; } ;
struct TYPE_3__ {size_t qtail; struct rx_device_buffer* rx_dev_buff; } ;
struct ks_wlan_private {int /*<<< orphan*/  rx_bh_task; TYPE_2__ psstatus; int /*<<< orphan*/  net_dev; TYPE_1__ rx_dev; } ;
struct hostif_hdr {int /*<<< orphan*/  event; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_WINDOW ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  READ_STATUS_REG ; 
 int /*<<< orphan*/  REG_STATUS_IDLE ; 
 int RX_DEVICE_BUFF_SIZE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hif_align_size (size_t) ; 
 int /*<<< orphan*/  inc_rxqtail (struct ks_wlan_private*) ; 
 scalar_t__ is_hif_conf (void*) ; 
 int ks7010_sdio_read (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ks7010_sdio_writeb (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int rxq_count (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ks_wlan_hw_rx(struct ks_wlan_private *priv, size_t size)
{
	int ret;
	struct rx_device_buffer *rx_buffer;
	struct hostif_hdr *hdr;
	u16 event = 0;

	/* receive data */
	if (rxq_count(priv) >= (RX_DEVICE_BUFF_SIZE - 1)) {
		netdev_err(priv->net_dev, "rx buffer overflow\n");
		return;
	}
	rx_buffer = &priv->rx_dev.rx_dev_buff[priv->rx_dev.qtail];

	ret = ks7010_sdio_read(priv, DATA_WINDOW, &rx_buffer->data[0],
			       hif_align_size(size));
	if (ret)
		return;

	/* length check */
	if (size > 2046 || size == 0) {
#ifdef DEBUG
		print_hex_dump_bytes("INVALID DATA dump: ",
				     DUMP_PREFIX_OFFSET,
				     rx_buffer->data, 32);
#endif
		ret = ks7010_sdio_writeb(priv, READ_STATUS_REG, REG_STATUS_IDLE);
		if (ret)
			netdev_err(priv->net_dev, "write READ_STATUS_REG\n");

		/* length check fail */
		return;
	}

	hdr = (struct hostif_hdr *)&rx_buffer->data[0];
	rx_buffer->size = le16_to_cpu(hdr->size) + sizeof(hdr->size);
	event = le16_to_cpu(hdr->event);
	inc_rxqtail(priv);

	ret = ks7010_sdio_writeb(priv, READ_STATUS_REG, REG_STATUS_IDLE);
	if (ret)
		netdev_err(priv->net_dev, "write READ_STATUS_REG\n");

	if (atomic_read(&priv->psstatus.confirm_wait) && is_hif_conf(event)) {
		netdev_dbg(priv->net_dev, "IS_HIF_CONF true !!\n");
		atomic_dec(&priv->psstatus.confirm_wait);
	}

	tasklet_schedule(&priv->rx_bh_task);
}