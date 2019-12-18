#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_6__ {int total_vfs; } ;
struct TYPE_5__ {int default_vid; int /*<<< orphan*/  max_queues; void* itr_scale; } ;
struct TYPE_4__ {int speed; } ;
struct fm10k_hw {TYPE_3__ iov; TYPE_2__ mac; TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_DGLORTDEC (int) ; 
 int /*<<< orphan*/  FM10K_DGLORTMAP (int) ; 
 int FM10K_DGLORTMAP_ANY ; 
 int FM10K_DGLORTMAP_NONE ; 
 int FM10K_DGLORT_COUNT ; 
 int /*<<< orphan*/  FM10K_DMA_CTRL ; 
 int FM10K_DMA_CTRL_32_DESC ; 
 int FM10K_DMA_CTRL_MAX_HOLD_1US_GEN1 ; 
 int FM10K_DMA_CTRL_MAX_HOLD_1US_GEN2 ; 
 int FM10K_DMA_CTRL_MAX_HOLD_1US_GEN3 ; 
 int FM10K_DMA_CTRL_MINMSS_64 ; 
 int FM10K_DMA_CTRL_RX_DESC_SIZE ; 
 int FM10K_DMA_CTRL_RX_ENABLE ; 
 int FM10K_DMA_CTRL_TX_ENABLE ; 
 int /*<<< orphan*/  FM10K_DTXTCPFLGH ; 
 int /*<<< orphan*/  FM10K_DTXTCPFLGL ; 
 int /*<<< orphan*/  FM10K_INT_CTRL ; 
 int FM10K_INT_CTRL_ENABLEMODERATOR ; 
 int /*<<< orphan*/  FM10K_ITR2 (int) ; 
 int FM10K_ITR_REG_COUNT_PF ; 
 int FM10K_MAX_QUEUES ; 
 int /*<<< orphan*/  FM10K_MAX_QUEUES_PF ; 
 void* FM10K_TDLEN_ITR_SCALE_GEN1 ; 
 void* FM10K_TDLEN_ITR_SCALE_GEN2 ; 
 void* FM10K_TDLEN_ITR_SCALE_GEN3 ; 
 int /*<<< orphan*/  FM10K_TPH_RXCTRL (int) ; 
 int FM10K_TPH_RXCTRL_DATA_WROEN ; 
 int FM10K_TPH_RXCTRL_DESC_RROEN ; 
 int FM10K_TPH_RXCTRL_DESC_TPHEN ; 
 int FM10K_TPH_RXCTRL_HDR_WROEN ; 
 int /*<<< orphan*/  FM10K_TPH_TXCTRL (int) ; 
 int FM10K_TPH_TXCTRL_DATA_RROEN ; 
 int FM10K_TPH_TXCTRL_DESC_RROEN ; 
 int FM10K_TPH_TXCTRL_DESC_TPHEN ; 
 int FM10K_TPH_TXCTRL_DESC_WROEN ; 
 int /*<<< orphan*/  FM10K_TQDLOC (int) ; 
 int FM10K_TQDLOC_BASE_32_DESC ; 
 int FM10K_TQDLOC_SIZE_32_DESC ; 
 int FM10K_TSO_FLAGS_HI ; 
 int FM10K_TSO_FLAGS_LOW ; 
 int /*<<< orphan*/  FM10K_TXQCTL (int) ; 
 int FM10K_TXQCTL_PF ; 
 int FM10K_TXQCTL_UNLIMITED_BW ; 
 int FM10K_TXQCTL_VID_SHIFT ; 
#define  fm10k_bus_speed_2500 130 
#define  fm10k_bus_speed_5000 129 
#define  fm10k_bus_speed_8000 128 
 int fm10k_dglort_default ; 
 scalar_t__ fm10k_is_ari_hierarchy_pf (struct fm10k_hw*) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 fm10k_init_hw_pf(struct fm10k_hw *hw)
{
	u32 dma_ctrl, txqctl;
	u16 i;

	/* Establish default VSI as valid */
	fm10k_write_reg(hw, FM10K_DGLORTDEC(fm10k_dglort_default), 0);
	fm10k_write_reg(hw, FM10K_DGLORTMAP(fm10k_dglort_default),
			FM10K_DGLORTMAP_ANY);

	/* Invalidate all other GLORT entries */
	for (i = 1; i < FM10K_DGLORT_COUNT; i++)
		fm10k_write_reg(hw, FM10K_DGLORTMAP(i), FM10K_DGLORTMAP_NONE);

	/* reset ITR2(0) to point to itself */
	fm10k_write_reg(hw, FM10K_ITR2(0), 0);

	/* reset VF ITR2(0) to point to 0 avoid PF registers */
	fm10k_write_reg(hw, FM10K_ITR2(FM10K_ITR_REG_COUNT_PF), 0);

	/* loop through all PF ITR2 registers pointing them to the previous */
	for (i = 1; i < FM10K_ITR_REG_COUNT_PF; i++)
		fm10k_write_reg(hw, FM10K_ITR2(i), i - 1);

	/* Enable interrupt moderator if not already enabled */
	fm10k_write_reg(hw, FM10K_INT_CTRL, FM10K_INT_CTRL_ENABLEMODERATOR);

	/* compute the default txqctl configuration */
	txqctl = FM10K_TXQCTL_PF | FM10K_TXQCTL_UNLIMITED_BW |
		 (hw->mac.default_vid << FM10K_TXQCTL_VID_SHIFT);

	for (i = 0; i < FM10K_MAX_QUEUES; i++) {
		/* configure rings for 256 Queue / 32 Descriptor cache mode */
		fm10k_write_reg(hw, FM10K_TQDLOC(i),
				(i * FM10K_TQDLOC_BASE_32_DESC) |
				FM10K_TQDLOC_SIZE_32_DESC);
		fm10k_write_reg(hw, FM10K_TXQCTL(i), txqctl);

		/* configure rings to provide TPH processing hints */
		fm10k_write_reg(hw, FM10K_TPH_TXCTRL(i),
				FM10K_TPH_TXCTRL_DESC_TPHEN |
				FM10K_TPH_TXCTRL_DESC_RROEN |
				FM10K_TPH_TXCTRL_DESC_WROEN |
				FM10K_TPH_TXCTRL_DATA_RROEN);
		fm10k_write_reg(hw, FM10K_TPH_RXCTRL(i),
				FM10K_TPH_RXCTRL_DESC_TPHEN |
				FM10K_TPH_RXCTRL_DESC_RROEN |
				FM10K_TPH_RXCTRL_DATA_WROEN |
				FM10K_TPH_RXCTRL_HDR_WROEN);
	}

	/* set max hold interval to align with 1.024 usec in all modes and
	 * store ITR scale
	 */
	switch (hw->bus.speed) {
	case fm10k_bus_speed_2500:
		dma_ctrl = FM10K_DMA_CTRL_MAX_HOLD_1US_GEN1;
		hw->mac.itr_scale = FM10K_TDLEN_ITR_SCALE_GEN1;
		break;
	case fm10k_bus_speed_5000:
		dma_ctrl = FM10K_DMA_CTRL_MAX_HOLD_1US_GEN2;
		hw->mac.itr_scale = FM10K_TDLEN_ITR_SCALE_GEN2;
		break;
	case fm10k_bus_speed_8000:
		dma_ctrl = FM10K_DMA_CTRL_MAX_HOLD_1US_GEN3;
		hw->mac.itr_scale = FM10K_TDLEN_ITR_SCALE_GEN3;
		break;
	default:
		dma_ctrl = 0;
		/* just in case, assume Gen3 ITR scale */
		hw->mac.itr_scale = FM10K_TDLEN_ITR_SCALE_GEN3;
		break;
	}

	/* Configure TSO flags */
	fm10k_write_reg(hw, FM10K_DTXTCPFLGL, FM10K_TSO_FLAGS_LOW);
	fm10k_write_reg(hw, FM10K_DTXTCPFLGH, FM10K_TSO_FLAGS_HI);

	/* Enable DMA engine
	 * Set Rx Descriptor size to 32
	 * Set Minimum MSS to 64
	 * Set Maximum number of Rx queues to 256 / 32 Descriptor
	 */
	dma_ctrl |= FM10K_DMA_CTRL_TX_ENABLE | FM10K_DMA_CTRL_RX_ENABLE |
		    FM10K_DMA_CTRL_RX_DESC_SIZE | FM10K_DMA_CTRL_MINMSS_64 |
		    FM10K_DMA_CTRL_32_DESC;

	fm10k_write_reg(hw, FM10K_DMA_CTRL, dma_ctrl);

	/* record maximum queue count, we limit ourselves to 128 */
	hw->mac.max_queues = FM10K_MAX_QUEUES_PF;

	/* We support either 64 VFs or 7 VFs depending on if we have ARI */
	hw->iov.total_vfs = fm10k_is_ari_hierarchy_pf(hw) ? 64 : 7;

	return 0;
}