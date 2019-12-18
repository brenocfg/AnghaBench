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
struct asd_dma_tok {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asd_dma_token_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct asd_dma_tok*) ; 

__attribute__((used)) static inline void asd_dmatok_free(struct asd_dma_tok *token)
{
	kmem_cache_free(asd_dma_token_cache, token);
}