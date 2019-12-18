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
struct omap_nand_info {int xfer_type; int gpmc_irq_fifo; int gpmc_irq_count; int ecc_opt; int /*<<< orphan*/  elm_dev; TYPE_3__* pdev; int /*<<< orphan*/  dma; int /*<<< orphan*/  phys_base; } ;
struct TYPE_5__ {int bytes; int size; int strength; void* write_subpage; void* write_page; void* read_page; void* correct; void* hwctl; void* mode; void* priv; void* calculate; int /*<<< orphan*/  algo; } ;
struct TYPE_4__ {int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; } ;
struct nand_chip {int bbt_options; int options; TYPE_2__ ecc; TYPE_1__ legacy; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct dma_slave_config {int src_maxburst; int dst_maxburst; void* dst_addr_width; void* src_addr_width; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
typedef  int /*<<< orphan*/  cfg ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int BADBLOCK_MARKER_LENGTH ; 
 int /*<<< orphan*/  BCH16_ECC ; 
 int /*<<< orphan*/  BCH4_ECC ; 
 int /*<<< orphan*/  BCH8_ECC ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 void* DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int NAND_BBT_NO_OOB ; 
 int NAND_BBT_USE_FLASH ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 void* NAND_ECC_HW ; 
 void* NAND_ECC_SOFT ; 
#define  NAND_OMAP_POLLED 137 
#define  NAND_OMAP_PREFETCH_DMA 136 
#define  NAND_OMAP_PREFETCH_IRQ 135 
#define  NAND_OMAP_PREFETCH_POLLED 134 
 int NAND_SKIP_BBTSCAN ; 
#define  OMAP_ECC_BCH16_CODE_HW 133 
#define  OMAP_ECC_BCH4_CODE_HW 132 
#define  OMAP_ECC_BCH4_CODE_HW_DETECTION_SW 131 
#define  OMAP_ECC_BCH8_CODE_HW 130 
#define  OMAP_ECC_BCH8_CODE_HW_DETECTION_SW 129 
#define  OMAP_ECC_HAM1_CODE_HW 128 
 int OMAP_ECC_HAM1_CODE_SW ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct omap_nand_info*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_chan (int /*<<< orphan*/ ,char*) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 
 int elm_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  memset (struct dma_slave_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 struct omap_nand_info* mtd_to_omap (struct mtd_info*) ; 
 void* nand_bch_correct_data ; 
 void* nand_bch_init (struct mtd_info*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  omap2_nand_ecc_check (struct omap_nand_info*) ; 
 void* omap_calculate_ecc ; 
 void* omap_calculate_ecc_bch_sw ; 
 void* omap_correct_data ; 
 void* omap_elm_correct_data ; 
 void* omap_enable_hwecc ; 
 void* omap_enable_hwecc_bch ; 
 int /*<<< orphan*/  omap_nand_irq ; 
 int /*<<< orphan*/  omap_ooblayout_ops ; 
 int /*<<< orphan*/  omap_read_buf_dma_pref ; 
 int /*<<< orphan*/  omap_read_buf_irq_pref ; 
 int /*<<< orphan*/  omap_read_buf_pref ; 
 void* omap_read_page_bch ; 
 int /*<<< orphan*/  omap_sw_ooblayout_ops ; 
 int /*<<< orphan*/  omap_write_buf_dma_pref ; 
 int /*<<< orphan*/  omap_write_buf_irq_pref ; 
 int /*<<< orphan*/  omap_write_buf_pref ; 
 void* omap_write_page_bch ; 
 void* omap_write_subpage_bch ; 
 void* platform_get_irq (TYPE_3__*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int omap_nand_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct omap_nand_info *info = mtd_to_omap(mtd);
	struct device *dev = &info->pdev->dev;
	int min_oobbytes = BADBLOCK_MARKER_LENGTH;
	int oobbytes_per_step;
	dma_cap_mask_t mask;
	int err;

	if (chip->bbt_options & NAND_BBT_USE_FLASH)
		chip->bbt_options |= NAND_BBT_NO_OOB;
	else
		chip->options |= NAND_SKIP_BBTSCAN;

	/* Re-populate low-level callbacks based on xfer modes */
	switch (info->xfer_type) {
	case NAND_OMAP_PREFETCH_POLLED:
		chip->legacy.read_buf = omap_read_buf_pref;
		chip->legacy.write_buf = omap_write_buf_pref;
		break;

	case NAND_OMAP_POLLED:
		/* Use nand_base defaults for {read,write}_buf */
		break;

	case NAND_OMAP_PREFETCH_DMA:
		dma_cap_zero(mask);
		dma_cap_set(DMA_SLAVE, mask);
		info->dma = dma_request_chan(dev->parent, "rxtx");

		if (IS_ERR(info->dma)) {
			dev_err(dev, "DMA engine request failed\n");
			return PTR_ERR(info->dma);
		} else {
			struct dma_slave_config cfg;

			memset(&cfg, 0, sizeof(cfg));
			cfg.src_addr = info->phys_base;
			cfg.dst_addr = info->phys_base;
			cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
			cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
			cfg.src_maxburst = 16;
			cfg.dst_maxburst = 16;
			err = dmaengine_slave_config(info->dma, &cfg);
			if (err) {
				dev_err(dev,
					"DMA engine slave config failed: %d\n",
					err);
				return err;
			}
			chip->legacy.read_buf = omap_read_buf_dma_pref;
			chip->legacy.write_buf = omap_write_buf_dma_pref;
		}
		break;

	case NAND_OMAP_PREFETCH_IRQ:
		info->gpmc_irq_fifo = platform_get_irq(info->pdev, 0);
		if (info->gpmc_irq_fifo <= 0) {
			dev_err(dev, "Error getting fifo IRQ\n");
			return -ENODEV;
		}
		err = devm_request_irq(dev, info->gpmc_irq_fifo,
				       omap_nand_irq, IRQF_SHARED,
				       "gpmc-nand-fifo", info);
		if (err) {
			dev_err(dev, "Requesting IRQ %d, error %d\n",
				info->gpmc_irq_fifo, err);
			info->gpmc_irq_fifo = 0;
			return err;
		}

		info->gpmc_irq_count = platform_get_irq(info->pdev, 1);
		if (info->gpmc_irq_count <= 0) {
			dev_err(dev, "Error getting IRQ count\n");
			return -ENODEV;
		}
		err = devm_request_irq(dev, info->gpmc_irq_count,
				       omap_nand_irq, IRQF_SHARED,
				       "gpmc-nand-count", info);
		if (err) {
			dev_err(dev, "Requesting IRQ %d, error %d\n",
				info->gpmc_irq_count, err);
			info->gpmc_irq_count = 0;
			return err;
		}

		chip->legacy.read_buf = omap_read_buf_irq_pref;
		chip->legacy.write_buf = omap_write_buf_irq_pref;

		break;

	default:
		dev_err(dev, "xfer_type %d not supported!\n", info->xfer_type);
		return -EINVAL;
	}

	if (!omap2_nand_ecc_check(info))
		return -EINVAL;

	/*
	 * Bail out earlier to let NAND_ECC_SOFT code create its own
	 * ooblayout instead of using ours.
	 */
	if (info->ecc_opt == OMAP_ECC_HAM1_CODE_SW) {
		chip->ecc.mode = NAND_ECC_SOFT;
		chip->ecc.algo = NAND_ECC_HAMMING;
		return 0;
	}

	/* Populate MTD interface based on ECC scheme */
	switch (info->ecc_opt) {
	case OMAP_ECC_HAM1_CODE_HW:
		dev_info(dev, "nand: using OMAP_ECC_HAM1_CODE_HW\n");
		chip->ecc.mode		= NAND_ECC_HW;
		chip->ecc.bytes		= 3;
		chip->ecc.size		= 512;
		chip->ecc.strength	= 1;
		chip->ecc.calculate	= omap_calculate_ecc;
		chip->ecc.hwctl		= omap_enable_hwecc;
		chip->ecc.correct	= omap_correct_data;
		mtd_set_ooblayout(mtd, &omap_ooblayout_ops);
		oobbytes_per_step	= chip->ecc.bytes;

		if (!(chip->options & NAND_BUSWIDTH_16))
			min_oobbytes	= 1;

		break;

	case OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
		pr_info("nand: using OMAP_ECC_BCH4_CODE_HW_DETECTION_SW\n");
		chip->ecc.mode		= NAND_ECC_HW;
		chip->ecc.size		= 512;
		chip->ecc.bytes		= 7;
		chip->ecc.strength	= 4;
		chip->ecc.hwctl		= omap_enable_hwecc_bch;
		chip->ecc.correct	= nand_bch_correct_data;
		chip->ecc.calculate	= omap_calculate_ecc_bch_sw;
		mtd_set_ooblayout(mtd, &omap_sw_ooblayout_ops);
		/* Reserve one byte for the OMAP marker */
		oobbytes_per_step	= chip->ecc.bytes + 1;
		/* Software BCH library is used for locating errors */
		chip->ecc.priv		= nand_bch_init(mtd);
		if (!chip->ecc.priv) {
			dev_err(dev, "Unable to use BCH library\n");
			return -EINVAL;
		}
		break;

	case OMAP_ECC_BCH4_CODE_HW:
		pr_info("nand: using OMAP_ECC_BCH4_CODE_HW ECC scheme\n");
		chip->ecc.mode		= NAND_ECC_HW;
		chip->ecc.size		= 512;
		/* 14th bit is kept reserved for ROM-code compatibility */
		chip->ecc.bytes		= 7 + 1;
		chip->ecc.strength	= 4;
		chip->ecc.hwctl		= omap_enable_hwecc_bch;
		chip->ecc.correct	= omap_elm_correct_data;
		chip->ecc.read_page	= omap_read_page_bch;
		chip->ecc.write_page	= omap_write_page_bch;
		chip->ecc.write_subpage	= omap_write_subpage_bch;
		mtd_set_ooblayout(mtd, &omap_ooblayout_ops);
		oobbytes_per_step	= chip->ecc.bytes;

		err = elm_config(info->elm_dev, BCH4_ECC,
				 mtd->writesize / chip->ecc.size,
				 chip->ecc.size, chip->ecc.bytes);
		if (err < 0)
			return err;
		break;

	case OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
		pr_info("nand: using OMAP_ECC_BCH8_CODE_HW_DETECTION_SW\n");
		chip->ecc.mode		= NAND_ECC_HW;
		chip->ecc.size		= 512;
		chip->ecc.bytes		= 13;
		chip->ecc.strength	= 8;
		chip->ecc.hwctl		= omap_enable_hwecc_bch;
		chip->ecc.correct	= nand_bch_correct_data;
		chip->ecc.calculate	= omap_calculate_ecc_bch_sw;
		mtd_set_ooblayout(mtd, &omap_sw_ooblayout_ops);
		/* Reserve one byte for the OMAP marker */
		oobbytes_per_step	= chip->ecc.bytes + 1;
		/* Software BCH library is used for locating errors */
		chip->ecc.priv		= nand_bch_init(mtd);
		if (!chip->ecc.priv) {
			dev_err(dev, "unable to use BCH library\n");
			return -EINVAL;
		}
		break;

	case OMAP_ECC_BCH8_CODE_HW:
		pr_info("nand: using OMAP_ECC_BCH8_CODE_HW ECC scheme\n");
		chip->ecc.mode		= NAND_ECC_HW;
		chip->ecc.size		= 512;
		/* 14th bit is kept reserved for ROM-code compatibility */
		chip->ecc.bytes		= 13 + 1;
		chip->ecc.strength	= 8;
		chip->ecc.hwctl		= omap_enable_hwecc_bch;
		chip->ecc.correct	= omap_elm_correct_data;
		chip->ecc.read_page	= omap_read_page_bch;
		chip->ecc.write_page	= omap_write_page_bch;
		chip->ecc.write_subpage	= omap_write_subpage_bch;
		mtd_set_ooblayout(mtd, &omap_ooblayout_ops);
		oobbytes_per_step	= chip->ecc.bytes;

		err = elm_config(info->elm_dev, BCH8_ECC,
				 mtd->writesize / chip->ecc.size,
				 chip->ecc.size, chip->ecc.bytes);
		if (err < 0)
			return err;

		break;

	case OMAP_ECC_BCH16_CODE_HW:
		pr_info("Using OMAP_ECC_BCH16_CODE_HW ECC scheme\n");
		chip->ecc.mode		= NAND_ECC_HW;
		chip->ecc.size		= 512;
		chip->ecc.bytes		= 26;
		chip->ecc.strength	= 16;
		chip->ecc.hwctl		= omap_enable_hwecc_bch;
		chip->ecc.correct	= omap_elm_correct_data;
		chip->ecc.read_page	= omap_read_page_bch;
		chip->ecc.write_page	= omap_write_page_bch;
		chip->ecc.write_subpage	= omap_write_subpage_bch;
		mtd_set_ooblayout(mtd, &omap_ooblayout_ops);
		oobbytes_per_step	= chip->ecc.bytes;

		err = elm_config(info->elm_dev, BCH16_ECC,
				 mtd->writesize / chip->ecc.size,
				 chip->ecc.size, chip->ecc.bytes);
		if (err < 0)
			return err;

		break;
	default:
		dev_err(dev, "Invalid or unsupported ECC scheme\n");
		return -EINVAL;
	}

	/* Check if NAND device's OOB is enough to store ECC signatures */
	min_oobbytes += (oobbytes_per_step *
			 (mtd->writesize / chip->ecc.size));
	if (mtd->oobsize < min_oobbytes) {
		dev_err(dev,
			"Not enough OOB bytes: required = %d, available=%d\n",
			min_oobbytes, mtd->oobsize);
		return -EINVAL;
	}

	return 0;
}