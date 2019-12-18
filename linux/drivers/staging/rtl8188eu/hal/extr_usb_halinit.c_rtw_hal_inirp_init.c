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
typedef  int /*<<< orphan*/  uint ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct recv_priv {struct recv_buf* precv_buf; } ;
struct recv_buf {int dummy; } ;
struct adapter {struct recv_priv recvpriv; } ;

/* Variables and functions */
 scalar_t__ NR_RECVBUFF ; 
 int /*<<< orphan*/  RECV_BULK_IN_ADDR ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 
 int /*<<< orphan*/  usb_read_port (struct adapter*,int /*<<< orphan*/ ,struct recv_buf*) ; 

u32 rtw_hal_inirp_init(struct adapter *Adapter)
{
	u8 i;
	struct recv_buf *precvbuf;
	uint	status;
	struct recv_priv *precvpriv = &Adapter->recvpriv;

	status = _SUCCESS;

	RT_TRACE(_module_hci_hal_init_c_, _drv_info_,
		 ("===> usb_inirp_init\n"));

	/* issue Rx irp to receive data */
	precvbuf = precvpriv->precv_buf;
	for (i = 0; i < NR_RECVBUFF; i++) {
		if (!usb_read_port(Adapter, RECV_BULK_IN_ADDR, precvbuf)) {
			RT_TRACE(_module_hci_hal_init_c_, _drv_err_, ("usb_rx_init: usb_read_port error\n"));
			status = _FAIL;
			goto exit;
		}

		precvbuf++;
	}

exit:

	RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("<=== usb_inirp_init\n"));

	return status;
}