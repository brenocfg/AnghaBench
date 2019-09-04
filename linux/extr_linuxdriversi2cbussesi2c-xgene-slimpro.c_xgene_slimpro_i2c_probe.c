#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  of_node; TYPE_7__* parent; } ;
struct i2c_adapter {TYPE_16__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; } ;
struct mbox_client {int knows_txdone; int tx_block; int /*<<< orphan*/  rx_callback; int /*<<< orphan*/  tx_tout; TYPE_7__* dev; } ;
struct slimpro_i2c_dev {TYPE_3__* mbox_chan; struct i2c_adapter adapter; void* pcc_comm_addr; int /*<<< orphan*/  comm_base_addr; int /*<<< orphan*/  mbox_idx; int /*<<< orphan*/  rd_complete; struct mbox_client mbox_client; TYPE_7__* dev; } ;
struct TYPE_22__ {int /*<<< orphan*/  of_node; TYPE_1__* driver; } ;
struct platform_device {TYPE_7__ dev; } ;
struct acpi_pcct_hw_reduced {int /*<<< orphan*/  length; int /*<<< orphan*/  base_address; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct TYPE_21__ {TYPE_2__* mbox; struct acpi_pcct_hw_reduced* con_priv; } ;
struct TYPE_20__ {int /*<<< orphan*/  txdone_irq; } ;
struct TYPE_19__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (TYPE_7__*) ; 
 int /*<<< orphan*/  ACPI_COMPANION_SET (TYPE_16__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  MAILBOX_I2C_INDEX ; 
 int /*<<< orphan*/  MAILBOX_OP_TIMEOUT ; 
 int /*<<< orphan*/  MEMREMAP_WB ; 
 int /*<<< orphan*/  MEMREMAP_WT ; 
 int PTR_ERR (TYPE_3__*) ; 
 int XGENE_SLIMPRO_I2C_V1 ; 
 int XGENE_SLIMPRO_I2C_V2 ; 
 scalar_t__ acpi_disabled ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_7__*,char*) ; 
 scalar_t__ device_property_read_u32 (TYPE_7__*,char*,int /*<<< orphan*/ *) ; 
 struct slimpro_i2c_dev* devm_kzalloc (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct slimpro_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_free_channel (TYPE_3__*) ; 
 TYPE_3__* mbox_request_channel (struct mbox_client*,int /*<<< orphan*/ ) ; 
 void* memremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcc_mbox_free_channel (TYPE_3__*) ; 
 TYPE_3__* pcc_mbox_request_channel (struct mbox_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct slimpro_i2c_dev*) ; 
 int /*<<< orphan*/  slimpro_i2c_pcc_rx_cb ; 
 int /*<<< orphan*/  slimpro_i2c_rx_cb ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  xgene_slimpro_i2c_algorithm ; 

__attribute__((used)) static int xgene_slimpro_i2c_probe(struct platform_device *pdev)
{
	struct slimpro_i2c_dev *ctx;
	struct i2c_adapter *adapter;
	struct mbox_client *cl;
	int rc;

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->dev = &pdev->dev;
	platform_set_drvdata(pdev, ctx);
	cl = &ctx->mbox_client;

	/* Request mailbox channel */
	cl->dev = &pdev->dev;
	init_completion(&ctx->rd_complete);
	cl->tx_tout = MAILBOX_OP_TIMEOUT;
	cl->knows_txdone = false;
	if (acpi_disabled) {
		cl->tx_block = true;
		cl->rx_callback = slimpro_i2c_rx_cb;
		ctx->mbox_chan = mbox_request_channel(cl, MAILBOX_I2C_INDEX);
		if (IS_ERR(ctx->mbox_chan)) {
			dev_err(&pdev->dev, "i2c mailbox channel request failed\n");
			return PTR_ERR(ctx->mbox_chan);
		}
	} else {
		struct acpi_pcct_hw_reduced *cppc_ss;
		const struct acpi_device_id *acpi_id;
		int version = XGENE_SLIMPRO_I2C_V1;

		acpi_id = acpi_match_device(pdev->dev.driver->acpi_match_table,
					    &pdev->dev);
		if (!acpi_id)
			return -EINVAL;

		version = (int)acpi_id->driver_data;

		if (device_property_read_u32(&pdev->dev, "pcc-channel",
					     &ctx->mbox_idx))
			ctx->mbox_idx = MAILBOX_I2C_INDEX;

		cl->tx_block = false;
		cl->rx_callback = slimpro_i2c_pcc_rx_cb;
		ctx->mbox_chan = pcc_mbox_request_channel(cl, ctx->mbox_idx);
		if (IS_ERR(ctx->mbox_chan)) {
			dev_err(&pdev->dev, "PCC mailbox channel request failed\n");
			return PTR_ERR(ctx->mbox_chan);
		}

		/*
		 * The PCC mailbox controller driver should
		 * have parsed the PCCT (global table of all
		 * PCC channels) and stored pointers to the
		 * subspace communication region in con_priv.
		 */
		cppc_ss = ctx->mbox_chan->con_priv;
		if (!cppc_ss) {
			dev_err(&pdev->dev, "PPC subspace not found\n");
			rc = -ENOENT;
			goto mbox_err;
		}

		if (!ctx->mbox_chan->mbox->txdone_irq) {
			dev_err(&pdev->dev, "PCC IRQ not supported\n");
			rc = -ENOENT;
			goto mbox_err;
		}

		/*
		 * This is the shared communication region
		 * for the OS and Platform to communicate over.
		 */
		ctx->comm_base_addr = cppc_ss->base_address;
		if (ctx->comm_base_addr) {
			if (version == XGENE_SLIMPRO_I2C_V2)
				ctx->pcc_comm_addr = memremap(
							ctx->comm_base_addr,
							cppc_ss->length,
							MEMREMAP_WT);
			else
				ctx->pcc_comm_addr = memremap(
							ctx->comm_base_addr,
							cppc_ss->length,
							MEMREMAP_WB);
		} else {
			dev_err(&pdev->dev, "Failed to get PCC comm region\n");
			rc = -ENOENT;
			goto mbox_err;
		}

		if (!ctx->pcc_comm_addr) {
			dev_err(&pdev->dev,
				"Failed to ioremap PCC comm region\n");
			rc = -ENOMEM;
			goto mbox_err;
		}
	}
	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (rc)
		dev_warn(&pdev->dev, "Unable to set dma mask\n");

	/* Setup I2C adapter */
	adapter = &ctx->adapter;
	snprintf(adapter->name, sizeof(adapter->name), "MAILBOX I2C");
	adapter->algo = &xgene_slimpro_i2c_algorithm;
	adapter->class = I2C_CLASS_HWMON;
	adapter->dev.parent = &pdev->dev;
	adapter->dev.of_node = pdev->dev.of_node;
	ACPI_COMPANION_SET(&adapter->dev, ACPI_COMPANION(&pdev->dev));
	i2c_set_adapdata(adapter, ctx);
	rc = i2c_add_adapter(adapter);
	if (rc)
		goto mbox_err;

	dev_info(&pdev->dev, "Mailbox I2C Adapter registered\n");
	return 0;

mbox_err:
	if (acpi_disabled)
		mbox_free_channel(ctx->mbox_chan);
	else
		pcc_mbox_free_channel(ctx->mbox_chan);

	return rc;
}