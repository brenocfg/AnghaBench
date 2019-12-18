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
struct ulptx_idata {void* len; void* cmd_more; } ;
struct TYPE_2__ {void* wr_hi; } ;
struct ulp_mem_io {void* len16; void* lock_addr; void* dlen; void* cmd; TYPE_1__ wr; } ;
struct sk_buff {int dummy; } ;
struct cxgbit_device {int dummy; } ;
struct cxgbi_ppm {unsigned int llimit; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  FW_ULPTX_WR ; 
 unsigned int FW_WR_ATOMIC_V (int /*<<< orphan*/ ) ; 
 unsigned int FW_WR_OP_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_ULPTX_WR (struct ulp_mem_io*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int PPOD_SIZE_SHIFT ; 
 unsigned int T5_ULP_MEMIO_IMM_V (int) ; 
 unsigned int ULPTX_CMD_V (int /*<<< orphan*/ ) ; 
 unsigned int ULP_MEMIO_ADDR_V (unsigned int) ; 
 unsigned int ULP_MEMIO_DATA_LEN_V (unsigned int) ; 
 unsigned int ULP_MEMIO_ORDER_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULP_TX_MEM_WRITE ; 
 int /*<<< orphan*/  ULP_TX_SC_IMM ; 
 struct ulp_mem_io* __skb_put (struct sk_buff*,unsigned int) ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 void* htonl (unsigned int) ; 
 unsigned int roundup (int,int) ; 

__attribute__((used)) static struct sk_buff *
cxgbit_ppod_init_idata(struct cxgbit_device *cdev, struct cxgbi_ppm *ppm,
		       unsigned int idx, unsigned int npods, unsigned int tid)
{
	struct ulp_mem_io *req;
	struct ulptx_idata *idata;
	unsigned int pm_addr = (idx << PPOD_SIZE_SHIFT) + ppm->llimit;
	unsigned int dlen = npods << PPOD_SIZE_SHIFT;
	unsigned int wr_len = roundup(sizeof(struct ulp_mem_io) +
				sizeof(struct ulptx_idata) + dlen, 16);
	struct sk_buff *skb;

	skb  = alloc_skb(wr_len, GFP_KERNEL);
	if (!skb)
		return NULL;

	req = __skb_put(skb, wr_len);
	INIT_ULPTX_WR(req, wr_len, 0, tid);
	req->wr.wr_hi = htonl(FW_WR_OP_V(FW_ULPTX_WR) |
		FW_WR_ATOMIC_V(0));
	req->cmd = htonl(ULPTX_CMD_V(ULP_TX_MEM_WRITE) |
		ULP_MEMIO_ORDER_V(0) |
		T5_ULP_MEMIO_IMM_V(1));
	req->dlen = htonl(ULP_MEMIO_DATA_LEN_V(dlen >> 5));
	req->lock_addr = htonl(ULP_MEMIO_ADDR_V(pm_addr >> 5));
	req->len16 = htonl(DIV_ROUND_UP(wr_len - sizeof(req->wr), 16));

	idata = (struct ulptx_idata *)(req + 1);
	idata->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM));
	idata->len = htonl(dlen);

	return skb;
}