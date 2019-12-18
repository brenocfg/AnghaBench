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
typedef  int u64 ;
struct siw_rx_stream {int dummy; } ;
struct siw_pbl {int dummy; } ;
struct siw_mem {int va; struct siw_pbl* pbl; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int min (int,int) ; 
 scalar_t__ siw_pbl_get_buffer (struct siw_pbl*,int,int*,int*) ; 
 int siw_rx_kva (struct siw_rx_stream*,void*,int) ; 

__attribute__((used)) static int siw_rx_pbl(struct siw_rx_stream *srx, int *pbl_idx,
		      struct siw_mem *mem, u64 addr, int len)
{
	struct siw_pbl *pbl = mem->pbl;
	u64 offset = addr - mem->va;
	int copied = 0;

	while (len) {
		int bytes;
		dma_addr_t buf_addr =
			siw_pbl_get_buffer(pbl, offset, &bytes, pbl_idx);
		if (!buf_addr)
			break;

		bytes = min(bytes, len);
		if (siw_rx_kva(srx, (void *)buf_addr, bytes) == bytes) {
			copied += bytes;
			offset += bytes;
			len -= bytes;
		} else {
			break;
		}
	}
	return copied;
}