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
struct TYPE_2__ {int va; int wptr; int pktsz; int memsz; } ;
struct rxf_fifo {TYPE_1__ m; } ;
struct rxf_desc {void* len; void* pa_hi; void* pa_lo; int /*<<< orphan*/  va_lo; void* info; } ;
struct rxdb {int dummy; } ;
struct rxd_desc {int /*<<< orphan*/  va_lo; } ;
struct rx_map {int /*<<< orphan*/  dma; } ;
struct bdx_priv {struct rxdb* rxdb; struct rxf_fifo rxf_fifo0; } ;

/* Variables and functions */
 void* CPU_CHIP_SWAP32 (int) ; 
 int /*<<< orphan*/  DBG (char*,...) ; 
 int /*<<< orphan*/  ENTER ; 
 int H32_64 (int /*<<< orphan*/ ) ; 
 int L32_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RET () ; 
 struct rx_map* bdx_rxdb_addr_elem (struct rxdb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int,int,int) ; 
 int /*<<< orphan*/  print_rxfd (struct rxf_desc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void bdx_recycle_skb(struct bdx_priv *priv, struct rxd_desc *rxdd)
{
	struct rxf_desc *rxfd;
	struct rx_map *dm;
	struct rxf_fifo *f;
	struct rxdb *db;
	int delta;

	ENTER;
	DBG("priv=%p rxdd=%p\n", priv, rxdd);
	f = &priv->rxf_fifo0;
	db = priv->rxdb;
	DBG("db=%p f=%p\n", db, f);
	dm = bdx_rxdb_addr_elem(db, rxdd->va_lo);
	DBG("dm=%p\n", dm);
	rxfd = (struct rxf_desc *)(f->m.va + f->m.wptr);
	rxfd->info = CPU_CHIP_SWAP32(0x10003);	/* INFO=1 BC=3 */
	rxfd->va_lo = rxdd->va_lo;
	rxfd->pa_lo = CPU_CHIP_SWAP32(L32_64(dm->dma));
	rxfd->pa_hi = CPU_CHIP_SWAP32(H32_64(dm->dma));
	rxfd->len = CPU_CHIP_SWAP32(f->m.pktsz);
	print_rxfd(rxfd);

	f->m.wptr += sizeof(struct rxf_desc);
	delta = f->m.wptr - f->m.memsz;
	if (unlikely(delta >= 0)) {
		f->m.wptr = delta;
		if (delta > 0) {
			memcpy(f->m.va, f->m.va + f->m.memsz, delta);
			DBG("wrapped descriptor\n");
		}
	}
	RET();
}