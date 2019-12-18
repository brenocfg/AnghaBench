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
struct asd_ha_struct {TYPE_1__* pcidev; } ;
struct asd_dma_tok {int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  asd_dmatok_free (struct asd_dma_tok*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void asd_free_coherent(struct asd_ha_struct *asd_ha,
				     struct asd_dma_tok *token)
{
	if (token) {
		dma_free_coherent(&asd_ha->pcidev->dev, token->size,
				  token->vaddr, token->dma_handle);
		asd_dmatok_free(token);
	}
}