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

/* Variables and functions */
 int CUDBG_QTYPE_CRYPTO_TXQ ; 
 int CUDBG_QTYPE_OFLD_TXQ ; 
 int CUDBG_QTYPE_UNKNOWN ; 
#define  CXGB4_TX_CRYPTO 129 
#define  CXGB4_TX_OFLD 128 

__attribute__((used)) static inline u32 cudbg_uld_txq_to_qtype(u32 uld)
{
	switch (uld) {
	case CXGB4_TX_OFLD:
		return CUDBG_QTYPE_OFLD_TXQ;
	case CXGB4_TX_CRYPTO:
		return CUDBG_QTYPE_CRYPTO_TXQ;
	}

	return CUDBG_QTYPE_UNKNOWN;
}