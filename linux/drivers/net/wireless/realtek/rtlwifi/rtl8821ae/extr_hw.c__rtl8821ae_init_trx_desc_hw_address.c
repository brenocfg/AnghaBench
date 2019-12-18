#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtl_priv {int dummy; } ;
struct rtl_pci {TYPE_2__* rx_ring; TYPE_1__* tx_ring; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int dma; } ;
struct TYPE_3__ {int dma; } ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 size_t BE_QUEUE ; 
 size_t BK_QUEUE ; 
 int DMA_BIT_MASK (int) ; 
 size_t HIGH_QUEUE ; 
 size_t MGNT_QUEUE ; 
 int /*<<< orphan*/  REG_BCNQ_DESA ; 
 int /*<<< orphan*/  REG_BEQ_DESA ; 
 int /*<<< orphan*/  REG_BKQ_DESA ; 
 int /*<<< orphan*/  REG_HQ_DESA ; 
 int /*<<< orphan*/  REG_MGQ_DESA ; 
 int /*<<< orphan*/  REG_RX_DESA ; 
 int /*<<< orphan*/  REG_VIQ_DESA ; 
 int /*<<< orphan*/  REG_VOQ_DESA ; 
 size_t RX_MPDU_QUEUE ; 
 size_t VI_QUEUE ; 
 size_t VO_QUEUE ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl8821ae_init_trx_desc_hw_address(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	/*low address*/
	rtl_write_dword(rtlpriv, REG_BCNQ_DESA,
			rtlpci->tx_ring[BEACON_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_MGQ_DESA,
			rtlpci->tx_ring[MGNT_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_VOQ_DESA,
			rtlpci->tx_ring[VO_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_VIQ_DESA,
			rtlpci->tx_ring[VI_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_BEQ_DESA,
			rtlpci->tx_ring[BE_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_BKQ_DESA,
			rtlpci->tx_ring[BK_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_HQ_DESA,
			rtlpci->tx_ring[HIGH_QUEUE].dma & DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_RX_DESA,
			rtlpci->rx_ring[RX_MPDU_QUEUE].dma & DMA_BIT_MASK(32));
}