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
typedef  int u32 ;
struct safexcel_crypto_priv {scalar_t__ version; int base; } ;

/* Variables and functions */
 scalar_t__ EIP197B ; 
 int EIP197B_CS_HT_WC ; 
 int EIP197B_CS_RC_MAX ; 
 int EIP197B_CS_TRC_LG_REC_WC ; 
 int EIP197B_CS_TRC_REC_WC ; 
 int EIP197D_CS_HT_WC ; 
 int EIP197D_CS_RC_MAX ; 
 int EIP197D_CS_TRC_LG_REC_WC ; 
 int EIP197D_CS_TRC_REC_WC ; 
 int EIP197_CLASSIFICATION_RAMS ; 
 int EIP197_CS_RAM_CTRL ; 
 int EIP197_CS_RC_NEXT (int) ; 
 int EIP197_CS_RC_PREV (int) ; 
 int EIP197_CS_RC_SIZE ; 
 int EIP197_RC_NULL ; 
 int EIP197_TRC_ECCCTRL ; 
 int EIP197_TRC_ENABLE_0 ; 
 int EIP197_TRC_ENABLE_MASK ; 
 int EIP197_TRC_FREECHAIN ; 
 int EIP197_TRC_FREECHAIN_HEAD_PTR (int /*<<< orphan*/ ) ; 
 int EIP197_TRC_FREECHAIN_TAIL_PTR (int) ; 
 int EIP197_TRC_PARAMS ; 
 int EIP197_TRC_PARAMS2 ; 
 int EIP197_TRC_PARAMS2_HTABLE_PTR (int) ; 
 int EIP197_TRC_PARAMS2_RC_SZ_SMALL (int) ; 
 int EIP197_TRC_PARAMS_BLK_TIMER_SPEED (int) ; 
 int EIP197_TRC_PARAMS_DATA_ACCESS ; 
 int EIP197_TRC_PARAMS_HTABLE_SZ (int) ; 
 int EIP197_TRC_PARAMS_RC_SZ_LARGE (int) ; 
 int EIP197_TRC_PARAMS_SW_RESET ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void eip197_trc_cache_init(struct safexcel_crypto_priv *priv)
{
	u32 val, htable_offset;
	int i, cs_rc_max, cs_ht_wc, cs_trc_rec_wc, cs_trc_lg_rec_wc;

	if (priv->version == EIP197B) {
		cs_rc_max = EIP197B_CS_RC_MAX;
		cs_ht_wc = EIP197B_CS_HT_WC;
		cs_trc_rec_wc = EIP197B_CS_TRC_REC_WC;
		cs_trc_lg_rec_wc = EIP197B_CS_TRC_LG_REC_WC;
	} else {
		cs_rc_max = EIP197D_CS_RC_MAX;
		cs_ht_wc = EIP197D_CS_HT_WC;
		cs_trc_rec_wc = EIP197D_CS_TRC_REC_WC;
		cs_trc_lg_rec_wc = EIP197D_CS_TRC_LG_REC_WC;
	}

	/* Enable the record cache memory access */
	val = readl(priv->base + EIP197_CS_RAM_CTRL);
	val &= ~EIP197_TRC_ENABLE_MASK;
	val |= EIP197_TRC_ENABLE_0;
	writel(val, priv->base + EIP197_CS_RAM_CTRL);

	/* Clear all ECC errors */
	writel(0, priv->base + EIP197_TRC_ECCCTRL);

	/*
	 * Make sure the cache memory is accessible by taking record cache into
	 * reset.
	 */
	val = readl(priv->base + EIP197_TRC_PARAMS);
	val |= EIP197_TRC_PARAMS_SW_RESET;
	val &= ~EIP197_TRC_PARAMS_DATA_ACCESS;
	writel(val, priv->base + EIP197_TRC_PARAMS);

	/* Clear all records */
	for (i = 0; i < cs_rc_max; i++) {
		u32 val, offset = EIP197_CLASSIFICATION_RAMS + i * EIP197_CS_RC_SIZE;

		writel(EIP197_CS_RC_NEXT(EIP197_RC_NULL) |
		       EIP197_CS_RC_PREV(EIP197_RC_NULL),
		       priv->base + offset);

		val = EIP197_CS_RC_NEXT(i+1) | EIP197_CS_RC_PREV(i-1);
		if (i == 0)
			val |= EIP197_CS_RC_PREV(EIP197_RC_NULL);
		else if (i == cs_rc_max - 1)
			val |= EIP197_CS_RC_NEXT(EIP197_RC_NULL);
		writel(val, priv->base + offset + sizeof(u32));
	}

	/* Clear the hash table entries */
	htable_offset = cs_rc_max * EIP197_CS_RC_SIZE;
	for (i = 0; i < cs_ht_wc; i++)
		writel(GENMASK(29, 0),
		       priv->base + EIP197_CLASSIFICATION_RAMS + htable_offset + i * sizeof(u32));

	/* Disable the record cache memory access */
	val = readl(priv->base + EIP197_CS_RAM_CTRL);
	val &= ~EIP197_TRC_ENABLE_MASK;
	writel(val, priv->base + EIP197_CS_RAM_CTRL);

	/* Write head and tail pointers of the record free chain */
	val = EIP197_TRC_FREECHAIN_HEAD_PTR(0) |
	      EIP197_TRC_FREECHAIN_TAIL_PTR(cs_rc_max - 1);
	writel(val, priv->base + EIP197_TRC_FREECHAIN);

	/* Configure the record cache #1 */
	val = EIP197_TRC_PARAMS2_RC_SZ_SMALL(cs_trc_rec_wc) |
	      EIP197_TRC_PARAMS2_HTABLE_PTR(cs_rc_max);
	writel(val, priv->base + EIP197_TRC_PARAMS2);

	/* Configure the record cache #2 */
	val = EIP197_TRC_PARAMS_RC_SZ_LARGE(cs_trc_lg_rec_wc) |
	      EIP197_TRC_PARAMS_BLK_TIMER_SPEED(1) |
	      EIP197_TRC_PARAMS_HTABLE_SZ(2);
	writel(val, priv->base + EIP197_TRC_PARAMS);
}