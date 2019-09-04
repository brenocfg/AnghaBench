#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rx_ring {int /*<<< orphan*/  lbq_buf_size; } ;
struct ql_adapter {int rss_ring_count; TYPE_1__* ndev; int /*<<< orphan*/  flags; struct rx_ring* rx_ring; int /*<<< orphan*/  lbq_buf_order; } ;
struct TYPE_4__ {int mtu; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  LARGE_BUFFER_MAX_SIZE ; 
 int /*<<< orphan*/  LARGE_BUFFER_MIN_SIZE ; 
 int /*<<< orphan*/  QL_ADAPTER_UP ; 
 int /*<<< orphan*/  dev_close (TYPE_1__*) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_alert (struct ql_adapter*,int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int ql_adapter_down (struct ql_adapter*) ; 
 int ql_adapter_up (struct ql_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_change_rx_buffers(struct ql_adapter *qdev)
{
	struct rx_ring *rx_ring;
	int i, status;
	u32 lbq_buf_len;

	/* Wait for an outstanding reset to complete. */
	if (!test_bit(QL_ADAPTER_UP, &qdev->flags)) {
		int i = 4;

		while (--i && !test_bit(QL_ADAPTER_UP, &qdev->flags)) {
			netif_err(qdev, ifup, qdev->ndev,
				  "Waiting for adapter UP...\n");
			ssleep(1);
		}

		if (!i) {
			netif_err(qdev, ifup, qdev->ndev,
				  "Timed out waiting for adapter UP\n");
			return -ETIMEDOUT;
		}
	}

	status = ql_adapter_down(qdev);
	if (status)
		goto error;

	/* Get the new rx buffer size. */
	lbq_buf_len = (qdev->ndev->mtu > 1500) ?
		LARGE_BUFFER_MAX_SIZE : LARGE_BUFFER_MIN_SIZE;
	qdev->lbq_buf_order = get_order(lbq_buf_len);

	for (i = 0; i < qdev->rss_ring_count; i++) {
		rx_ring = &qdev->rx_ring[i];
		/* Set the new size. */
		rx_ring->lbq_buf_size = lbq_buf_len;
	}

	status = ql_adapter_up(qdev);
	if (status)
		goto error;

	return status;
error:
	netif_alert(qdev, ifup, qdev->ndev,
		    "Driver up/down cycle failed, closing device.\n");
	set_bit(QL_ADAPTER_UP, &qdev->flags);
	dev_close(qdev->ndev);
	return status;
}