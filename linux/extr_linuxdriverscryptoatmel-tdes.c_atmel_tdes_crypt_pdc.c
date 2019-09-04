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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct crypto_tfm {int dummy; } ;
struct atmel_tdes_dev {int dma_size; int flags; int /*<<< orphan*/  dev; } ;
struct atmel_tdes_ctx {struct atmel_tdes_dev* dd; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int TDES_FLAGS_CFB ; 
 int TDES_FLAGS_CFB16 ; 
 int TDES_FLAGS_CFB8 ; 
 int TDES_FLAGS_FAST ; 
 int /*<<< orphan*/  TDES_IER ; 
 int TDES_INT_ENDRX ; 
 int /*<<< orphan*/  TDES_PTCR ; 
 int TDES_PTCR_RXTDIS ; 
 int TDES_PTCR_RXTEN ; 
 int TDES_PTCR_TXTDIS ; 
 int TDES_PTCR_TXTEN ; 
 int /*<<< orphan*/  TDES_RCR ; 
 int /*<<< orphan*/  TDES_RPR ; 
 int /*<<< orphan*/  TDES_TCR ; 
 int /*<<< orphan*/  TDES_TPR ; 
 int /*<<< orphan*/  atmel_tdes_write (struct atmel_tdes_dev*,int /*<<< orphan*/ ,int) ; 
 struct atmel_tdes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_tdes_crypt_pdc(struct crypto_tfm *tfm, dma_addr_t dma_addr_in,
			       dma_addr_t dma_addr_out, int length)
{
	struct atmel_tdes_ctx *ctx = crypto_tfm_ctx(tfm);
	struct atmel_tdes_dev *dd = ctx->dd;
	int len32;

	dd->dma_size = length;

	if (!(dd->flags & TDES_FLAGS_FAST)) {
		dma_sync_single_for_device(dd->dev, dma_addr_in, length,
					   DMA_TO_DEVICE);
	}

	if ((dd->flags & TDES_FLAGS_CFB) && (dd->flags & TDES_FLAGS_CFB8))
		len32 = DIV_ROUND_UP(length, sizeof(u8));
	else if ((dd->flags & TDES_FLAGS_CFB) && (dd->flags & TDES_FLAGS_CFB16))
		len32 = DIV_ROUND_UP(length, sizeof(u16));
	else
		len32 = DIV_ROUND_UP(length, sizeof(u32));

	atmel_tdes_write(dd, TDES_PTCR, TDES_PTCR_TXTDIS|TDES_PTCR_RXTDIS);
	atmel_tdes_write(dd, TDES_TPR, dma_addr_in);
	atmel_tdes_write(dd, TDES_TCR, len32);
	atmel_tdes_write(dd, TDES_RPR, dma_addr_out);
	atmel_tdes_write(dd, TDES_RCR, len32);

	/* Enable Interrupt */
	atmel_tdes_write(dd, TDES_IER, TDES_INT_ENDRX);

	/* Start DMA transfer */
	atmel_tdes_write(dd, TDES_PTCR, TDES_PTCR_TXTEN | TDES_PTCR_RXTEN);

	return 0;
}