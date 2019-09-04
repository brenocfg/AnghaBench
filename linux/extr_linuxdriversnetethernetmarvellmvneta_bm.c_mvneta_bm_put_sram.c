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
struct mvneta_bm {int /*<<< orphan*/  bppi_phys_addr; int /*<<< orphan*/  bppi_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_BM_BPPI_SIZE ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_bm_put_sram(struct mvneta_bm *priv)
{
	gen_pool_free(priv->bppi_pool, priv->bppi_phys_addr,
		      MVNETA_BM_BPPI_SIZE);
}