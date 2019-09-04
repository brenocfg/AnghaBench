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
struct artpec6_crypto_req_common {int /*<<< orphan*/ * dma; } ;
struct artpec6_crypto {int /*<<< orphan*/  dma_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  artpec6_crypto_bounce_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  artpec6_crypto_dev ; 
 int /*<<< orphan*/  artpec6_crypto_dma_unmap_all (struct artpec6_crypto_req_common*) ; 
 struct artpec6_crypto* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
artpec6_crypto_common_destroy(struct artpec6_crypto_req_common *common)
{
	struct artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);

	artpec6_crypto_dma_unmap_all(common);
	artpec6_crypto_bounce_destroy(common->dma);
	kmem_cache_free(ac->dma_cache, common->dma);
	common->dma = NULL;
	return 0;
}