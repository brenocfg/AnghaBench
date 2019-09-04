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
struct bnx2_napi {struct bnx2* bp; int /*<<< orphan*/  napi; } ;
struct bnx2 {int irq_nvecs; struct bnx2_napi* bnx2_napi; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int bnx2_poll (struct napi_struct*,int) ; 
 int bnx2_poll_msix (struct napi_struct*,int) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int (*) (struct napi_struct*,int),int) ; 

__attribute__((used)) static void
bnx2_init_napi(struct bnx2 *bp)
{
	int i;

	for (i = 0; i < bp->irq_nvecs; i++) {
		struct bnx2_napi *bnapi = &bp->bnx2_napi[i];
		int (*poll)(struct napi_struct *, int);

		if (i == 0)
			poll = bnx2_poll;
		else
			poll = bnx2_poll_msix;

		netif_napi_add(bp->dev, &bp->bnx2_napi[i].napi, poll, 64);
		bnapi->bp = bp;
	}
}