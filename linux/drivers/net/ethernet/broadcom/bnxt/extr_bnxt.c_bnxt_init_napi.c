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
struct bnxt_napi {int /*<<< orphan*/  napi; } ;
struct bnxt {unsigned int cp_nr_rings; int flags; int /*<<< orphan*/  dev; struct bnxt_napi** bnapi; } ;

/* Variables and functions */
 scalar_t__ BNXT_CHIP_TYPE_NITRO_A0 (struct bnxt*) ; 
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_USING_MSIX ; 
 int bnxt_poll (struct napi_struct*,int) ; 
 int bnxt_poll_nitroa0 (struct napi_struct*,int) ; 
 int bnxt_poll_p5 (struct napi_struct*,int) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int (*) (struct napi_struct*,int),int) ; 

__attribute__((used)) static void bnxt_init_napi(struct bnxt *bp)
{
	int i;
	unsigned int cp_nr_rings = bp->cp_nr_rings;
	struct bnxt_napi *bnapi;

	if (bp->flags & BNXT_FLAG_USING_MSIX) {
		int (*poll_fn)(struct napi_struct *, int) = bnxt_poll;

		if (bp->flags & BNXT_FLAG_CHIP_P5)
			poll_fn = bnxt_poll_p5;
		else if (BNXT_CHIP_TYPE_NITRO_A0(bp))
			cp_nr_rings--;
		for (i = 0; i < cp_nr_rings; i++) {
			bnapi = bp->bnapi[i];
			netif_napi_add(bp->dev, &bnapi->napi, poll_fn, 64);
		}
		if (BNXT_CHIP_TYPE_NITRO_A0(bp)) {
			bnapi = bp->bnapi[cp_nr_rings];
			netif_napi_add(bp->dev, &bnapi->napi,
				       bnxt_poll_nitroa0, 64);
		}
	} else {
		bnapi = bp->bnapi[0];
		netif_napi_add(bp->dev, &bnapi->napi, bnxt_poll, 64);
	}
}