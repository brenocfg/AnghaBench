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
struct TYPE_2__ {void* wr_hi; } ;
struct ulp_mem_io {void* len; void* cmd_lock_addr; TYPE_1__ wr; } ;
struct sk_buff {scalar_t__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_WROPCODE_BYPASS ; 
 int IPPOD_SIZE ; 
 int /*<<< orphan*/  ULP_MEM_WRITE ; 
 int V_ULPTX_CMD (int /*<<< orphan*/ ) ; 
 int V_ULPTX_NFLITS (int) ; 
 int V_ULP_MEMIO_ADDR (unsigned int) ; 
 int V_ULP_MEMIO_DATA_LEN (int) ; 
 int V_WR_OP (int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memset (struct ulp_mem_io*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ulp_mem_io_set_hdr(struct sk_buff *skb, unsigned int addr)
{
	struct ulp_mem_io *req = (struct ulp_mem_io *)skb->head;

	memset(req, 0, sizeof(*req));

	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_BYPASS));
	req->cmd_lock_addr = htonl(V_ULP_MEMIO_ADDR(addr >> 5) |
				   V_ULPTX_CMD(ULP_MEM_WRITE));
	req->len = htonl(V_ULP_MEMIO_DATA_LEN(IPPOD_SIZE >> 5) |
			 V_ULPTX_NFLITS((IPPOD_SIZE >> 3) + 1));
}