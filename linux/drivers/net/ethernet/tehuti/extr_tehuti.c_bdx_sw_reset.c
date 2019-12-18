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
struct bdx_priv {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int /*<<< orphan*/  ENTER ; 
 int READ_REG (struct bdx_priv*,int) ; 
 int /*<<< orphan*/  RET (int /*<<< orphan*/ ) ; 
 int TXF_WPTR_WR_PTR ; 
 int /*<<< orphan*/  WRITE_REG (struct bdx_priv*,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int regDIS_PORT ; 
 int regDIS_QU ; 
 int regGMAC_RXF_A ; 
 int regIMR ; 
 int regISR ; 
 int regRDINTCM0 ; 
 int regRST_PORT ; 
 int regRST_QU ; 
 int regTDINTCM0 ; 
 int regTXD_WPTR_0 ; 
 int regTXF_RPTR_3 ; 

__attribute__((used)) static int bdx_sw_reset(struct bdx_priv *priv)
{
	int i;

	ENTER;
	/* 1. load MAC (obsolete) */
	/* 2. disable Rx (and Tx) */
	WRITE_REG(priv, regGMAC_RXF_A, 0);
	mdelay(100);
	/* 3. disable port */
	WRITE_REG(priv, regDIS_PORT, 1);
	/* 4. disable queue */
	WRITE_REG(priv, regDIS_QU, 1);
	/* 5. wait until hw is disabled */
	for (i = 0; i < 50; i++) {
		if (READ_REG(priv, regRST_PORT) & 1)
			break;
		mdelay(10);
	}
	if (i == 50)
		netdev_err(priv->ndev, "SW reset timeout. continuing anyway\n");

	/* 6. disable intrs */
	WRITE_REG(priv, regRDINTCM0, 0);
	WRITE_REG(priv, regTDINTCM0, 0);
	WRITE_REG(priv, regIMR, 0);
	READ_REG(priv, regISR);

	/* 7. reset queue */
	WRITE_REG(priv, regRST_QU, 1);
	/* 8. reset port */
	WRITE_REG(priv, regRST_PORT, 1);
	/* 9. zero all read and write pointers */
	for (i = regTXD_WPTR_0; i <= regTXF_RPTR_3; i += 0x10)
		DBG("%x = %x\n", i, READ_REG(priv, i) & TXF_WPTR_WR_PTR);
	for (i = regTXD_WPTR_0; i <= regTXF_RPTR_3; i += 0x10)
		WRITE_REG(priv, i, 0);
	/* 10. unseet port disable */
	WRITE_REG(priv, regDIS_PORT, 0);
	/* 11. unset queue disable */
	WRITE_REG(priv, regDIS_QU, 0);
	/* 12. unset queue reset */
	WRITE_REG(priv, regRST_QU, 0);
	/* 13. unset port reset */
	WRITE_REG(priv, regRST_PORT, 0);
	/* 14. enable Rx */
	/* skiped. will be done later */
	/* 15. save MAC (obsolete) */
	for (i = regTXD_WPTR_0; i <= regTXF_RPTR_3; i += 0x10)
		DBG("%x = %x\n", i, READ_REG(priv, i) & TXF_WPTR_WR_PTR);

	RET(0);
}