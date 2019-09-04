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
struct rk_crypto_info {int total; scalar_t__ reg; int /*<<< orphan*/  async_req; } ;
struct rk_ahash_rctx {int mode; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int CRYPTO_READ (struct rk_crypto_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_WRITE (struct rk_crypto_info*,int /*<<< orphan*/ ,int) ; 
 int RK_CRYPTO_BYTESWAP_BRFIFO ; 
 int RK_CRYPTO_BYTESWAP_BTFIFO ; 
 int RK_CRYPTO_BYTESWAP_HRFIFO ; 
 int /*<<< orphan*/  RK_CRYPTO_CONF ; 
 int /*<<< orphan*/  RK_CRYPTO_CTRL ; 
 int /*<<< orphan*/  RK_CRYPTO_HASH_CTRL ; 
 scalar_t__ RK_CRYPTO_HASH_DOUT_0 ; 
 int RK_CRYPTO_HASH_FLUSH ; 
 int /*<<< orphan*/  RK_CRYPTO_HASH_MSG_LEN ; 
 int RK_CRYPTO_HASH_SWAP_DO ; 
 int RK_CRYPTO_HRDMA_DONE_ENA ; 
 int RK_CRYPTO_HRDMA_DONE_INT ; 
 int RK_CRYPTO_HRDMA_ERR_ENA ; 
 int RK_CRYPTO_HRDMA_ERR_INT ; 
 int /*<<< orphan*/  RK_CRYPTO_INTENA ; 
 int /*<<< orphan*/  RK_CRYPTO_INTSTS ; 
 int _SBF (int,int) ; 
 struct ahash_request* ahash_request_cast (int /*<<< orphan*/ ) ; 
 struct rk_ahash_rctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rk_ahash_reg_init(struct rk_crypto_info *dev)
{
	struct ahash_request *req = ahash_request_cast(dev->async_req);
	struct rk_ahash_rctx *rctx = ahash_request_ctx(req);
	int reg_status = 0;

	reg_status = CRYPTO_READ(dev, RK_CRYPTO_CTRL) |
		     RK_CRYPTO_HASH_FLUSH | _SBF(0xffff, 16);
	CRYPTO_WRITE(dev, RK_CRYPTO_CTRL, reg_status);

	reg_status = CRYPTO_READ(dev, RK_CRYPTO_CTRL);
	reg_status &= (~RK_CRYPTO_HASH_FLUSH);
	reg_status |= _SBF(0xffff, 16);
	CRYPTO_WRITE(dev, RK_CRYPTO_CTRL, reg_status);

	memset_io(dev->reg + RK_CRYPTO_HASH_DOUT_0, 0, 32);

	CRYPTO_WRITE(dev, RK_CRYPTO_INTENA, RK_CRYPTO_HRDMA_ERR_ENA |
					    RK_CRYPTO_HRDMA_DONE_ENA);

	CRYPTO_WRITE(dev, RK_CRYPTO_INTSTS, RK_CRYPTO_HRDMA_ERR_INT |
					    RK_CRYPTO_HRDMA_DONE_INT);

	CRYPTO_WRITE(dev, RK_CRYPTO_HASH_CTRL, rctx->mode |
					       RK_CRYPTO_HASH_SWAP_DO);

	CRYPTO_WRITE(dev, RK_CRYPTO_CONF, RK_CRYPTO_BYTESWAP_HRFIFO |
					  RK_CRYPTO_BYTESWAP_BRFIFO |
					  RK_CRYPTO_BYTESWAP_BTFIFO);

	CRYPTO_WRITE(dev, RK_CRYPTO_HASH_MSG_LEN, dev->total);
}