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
struct asd_dma_tok {size_t size; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  dma_handle; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct asd_dma_tok* asd_dmatok_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_dmatok_free (struct asd_dma_tok*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct asd_dma_tok *asd_alloc_coherent(struct asd_ha_struct *
						     asd_ha, size_t size,
						     gfp_t flags)
{
	struct asd_dma_tok *token = asd_dmatok_alloc(flags);
	if (token) {
		token->size = size;
		token->vaddr = dma_alloc_coherent(&asd_ha->pcidev->dev,
						  token->size,
						  &token->dma_handle,
						  flags);
		if (!token->vaddr) {
			asd_dmatok_free(token);
			token = NULL;
		}
	}
	return token;
}