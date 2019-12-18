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
typedef  scalar_t__ u16 ;
struct tx_ring {int wq_id; int wq_len; int wq_size; int cq_id; struct ql_adapter* qdev; } ;
struct rx_ring {int cq_id; int cpu; int cq_len; int cq_size; int lbq_len; int lbq_size; int sbq_len; int sbq_size; int /*<<< orphan*/  type; scalar_t__ sbq_buf_size; scalar_t__ lbq_buf_size; struct ql_adapter* qdev; } ;
struct ql_net_rsp_iocb {int dummy; } ;
struct ql_adapter {int intr_count; int rss_ring_count; int tx_ring_count; int rx_ring_count; int tx_ring_size; int rx_ring_size; struct rx_ring* rx_ring; struct tx_ring* tx_ring; int /*<<< orphan*/  lbq_buf_order; TYPE_1__* ndev; } ;
struct ob_mac_iocb_req {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int mtu; } ;

/* Variables and functions */
 unsigned int LARGE_BUFFER_MAX_SIZE ; 
 unsigned int LARGE_BUFFER_MIN_SIZE ; 
 int /*<<< orphan*/  MAX_CPUS ; 
 int NUM_LARGE_BUFFERS ; 
 int NUM_SMALL_BUFFERS ; 
 int /*<<< orphan*/  RX_Q ; 
 scalar_t__ SMALL_BUF_MAP_SIZE ; 
 int /*<<< orphan*/  TX_Q ; 
 int /*<<< orphan*/  get_order (unsigned int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 scalar_t__ num_online_cpus () ; 
 int /*<<< orphan*/  ql_enable_msix (struct ql_adapter*) ; 

__attribute__((used)) static int ql_configure_rings(struct ql_adapter *qdev)
{
	int i;
	struct rx_ring *rx_ring;
	struct tx_ring *tx_ring;
	int cpu_cnt = min(MAX_CPUS, (int)num_online_cpus());
	unsigned int lbq_buf_len = (qdev->ndev->mtu > 1500) ?
		LARGE_BUFFER_MAX_SIZE : LARGE_BUFFER_MIN_SIZE;

	qdev->lbq_buf_order = get_order(lbq_buf_len);

	/* In a perfect world we have one RSS ring for each CPU
	 * and each has it's own vector.  To do that we ask for
	 * cpu_cnt vectors.  ql_enable_msix() will adjust the
	 * vector count to what we actually get.  We then
	 * allocate an RSS ring for each.
	 * Essentially, we are doing min(cpu_count, msix_vector_count).
	 */
	qdev->intr_count = cpu_cnt;
	ql_enable_msix(qdev);
	/* Adjust the RSS ring count to the actual vector count. */
	qdev->rss_ring_count = qdev->intr_count;
	qdev->tx_ring_count = cpu_cnt;
	qdev->rx_ring_count = qdev->tx_ring_count + qdev->rss_ring_count;

	for (i = 0; i < qdev->tx_ring_count; i++) {
		tx_ring = &qdev->tx_ring[i];
		memset((void *)tx_ring, 0, sizeof(*tx_ring));
		tx_ring->qdev = qdev;
		tx_ring->wq_id = i;
		tx_ring->wq_len = qdev->tx_ring_size;
		tx_ring->wq_size =
		    tx_ring->wq_len * sizeof(struct ob_mac_iocb_req);

		/*
		 * The completion queue ID for the tx rings start
		 * immediately after the rss rings.
		 */
		tx_ring->cq_id = qdev->rss_ring_count + i;
	}

	for (i = 0; i < qdev->rx_ring_count; i++) {
		rx_ring = &qdev->rx_ring[i];
		memset((void *)rx_ring, 0, sizeof(*rx_ring));
		rx_ring->qdev = qdev;
		rx_ring->cq_id = i;
		rx_ring->cpu = i % cpu_cnt;	/* CPU to run handler on. */
		if (i < qdev->rss_ring_count) {
			/*
			 * Inbound (RSS) queues.
			 */
			rx_ring->cq_len = qdev->rx_ring_size;
			rx_ring->cq_size =
			    rx_ring->cq_len * sizeof(struct ql_net_rsp_iocb);
			rx_ring->lbq_len = NUM_LARGE_BUFFERS;
			rx_ring->lbq_size =
			    rx_ring->lbq_len * sizeof(__le64);
			rx_ring->lbq_buf_size = (u16)lbq_buf_len;
			rx_ring->sbq_len = NUM_SMALL_BUFFERS;
			rx_ring->sbq_size =
			    rx_ring->sbq_len * sizeof(__le64);
			rx_ring->sbq_buf_size = SMALL_BUF_MAP_SIZE;
			rx_ring->type = RX_Q;
		} else {
			/*
			 * Outbound queue handles outbound completions only.
			 */
			/* outbound cq is same size as tx_ring it services. */
			rx_ring->cq_len = qdev->tx_ring_size;
			rx_ring->cq_size =
			    rx_ring->cq_len * sizeof(struct ql_net_rsp_iocb);
			rx_ring->lbq_len = 0;
			rx_ring->lbq_size = 0;
			rx_ring->lbq_buf_size = 0;
			rx_ring->sbq_len = 0;
			rx_ring->sbq_size = 0;
			rx_ring->sbq_buf_size = 0;
			rx_ring->type = TX_Q;
		}
	}
	return 0;
}