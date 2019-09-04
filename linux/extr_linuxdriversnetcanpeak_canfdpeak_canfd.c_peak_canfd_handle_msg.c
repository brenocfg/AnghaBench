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
typedef  int u16 ;
struct pucan_status_msg {int dummy; } ;
struct pucan_rx_msg {int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct pucan_error_msg {int dummy; } ;
struct peak_canfd_priv {int dummy; } ;

/* Variables and functions */
#define  PUCAN_MSG_CACHE_CRITICAL 131 
#define  PUCAN_MSG_CAN_RX 130 
#define  PUCAN_MSG_ERROR 129 
#define  PUCAN_MSG_STATUS 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int pucan_handle_cache_critical (struct peak_canfd_priv*) ; 
 int pucan_handle_can_rx (struct peak_canfd_priv*,struct pucan_rx_msg*) ; 
 int pucan_handle_error (struct peak_canfd_priv*,struct pucan_error_msg*) ; 
 int pucan_handle_status (struct peak_canfd_priv*,struct pucan_status_msg*) ; 

int peak_canfd_handle_msg(struct peak_canfd_priv *priv,
			  struct pucan_rx_msg *msg)
{
	u16 msg_type = le16_to_cpu(msg->type);
	int msg_size = le16_to_cpu(msg->size);
	int err;

	if (!msg_size || !msg_type) {
		/* null packet found: end of list */
		goto exit;
	}

	switch (msg_type) {
	case PUCAN_MSG_CAN_RX:
		err = pucan_handle_can_rx(priv, (struct pucan_rx_msg *)msg);
		break;
	case PUCAN_MSG_ERROR:
		err = pucan_handle_error(priv, (struct pucan_error_msg *)msg);
		break;
	case PUCAN_MSG_STATUS:
		err = pucan_handle_status(priv, (struct pucan_status_msg *)msg);
		break;
	case PUCAN_MSG_CACHE_CRITICAL:
		err = pucan_handle_cache_critical(priv);
		break;
	default:
		err = 0;
	}

	if (err < 0)
		return err;

exit:
	return msg_size;
}