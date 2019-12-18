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
typedef  int u32 ;
struct sdio_func {int /*<<< orphan*/  cur_blksize; int /*<<< orphan*/  max_blksize; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  num; int /*<<< orphan*/  dev; } ;
struct sdio_device_id {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct ath10k_sdio_irq_proc_regs {int dummy; } ;
struct ath10k_sdio_irq_enable_regs {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtx; void* irq_en_reg; void* irq_proc_reg; } ;
struct ath10k_sdio {int is_disabled; int /*<<< orphan*/  workqueue; int /*<<< orphan*/ * bus_req; int /*<<< orphan*/  wr_async_work; int /*<<< orphan*/  wr_asyncq; int /*<<< orphan*/  bus_req_freeq; TYPE_1__ irq_data; int /*<<< orphan*/  wr_async_lock; int /*<<< orphan*/  lock; struct ath10k* ar; struct sdio_func* func; void* bmi_buf; } ;
struct ath10k_bus_params {int hl_msdu_ids; scalar_t__ chip_id; int /*<<< orphan*/  dev_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct ath10k {TYPE_2__ id; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  dev; } ;
typedef  enum ath10k_hw_rev { ____Placeholder_ath10k_hw_rev } ath10k_hw_rev ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_BUS_SDIO ; 
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ATH10K_DEV_TYPE_HL ; 
 int ATH10K_HW_QCA6174 ; 
 int ATH10K_SDIO_BUS_REQUEST_MAX_NUM ; 
 int BMI_MAX_CMDBUF_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QCA9377_1_0_DEVICE_ID ; 
#define  QCA_MANUFACTURER_ID_AR6005_BASE 129 
 int /*<<< orphan*/  QCA_MANUFACTURER_ID_BASE ; 
#define  QCA_MANUFACTURER_ID_QCA9377_BASE 128 
 struct ath10k* ath10k_core_create (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_core_destroy (struct ath10k*) ; 
 int ath10k_core_register (struct ath10k*,struct ath10k_bus_params*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int,...) ; 
 int /*<<< orphan*/  ath10k_sdio_free_bus_req (struct ath10k*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_sdio_hif_ops ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_sdio_set_mbox_info (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_sdio_write_async_work ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct ath10k_sdio*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_sdio_probe(struct sdio_func *func,
			     const struct sdio_device_id *id)
{
	struct ath10k_sdio *ar_sdio;
	struct ath10k *ar;
	enum ath10k_hw_rev hw_rev;
	u32 dev_id_base;
	struct ath10k_bus_params bus_params = {};
	int ret, i;

	/* Assumption: All SDIO based chipsets (so far) are QCA6174 based.
	 * If there will be newer chipsets that does not use the hw reg
	 * setup as defined in qca6174_regs and qca6174_values, this
	 * assumption is no longer valid and hw_rev must be setup differently
	 * depending on chipset.
	 */
	hw_rev = ATH10K_HW_QCA6174;

	ar = ath10k_core_create(sizeof(*ar_sdio), &func->dev, ATH10K_BUS_SDIO,
				hw_rev, &ath10k_sdio_hif_ops);
	if (!ar) {
		dev_err(&func->dev, "failed to allocate core\n");
		return -ENOMEM;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "sdio new func %d vendor 0x%x device 0x%x block 0x%x/0x%x\n",
		   func->num, func->vendor, func->device,
		   func->max_blksize, func->cur_blksize);

	ar_sdio = ath10k_sdio_priv(ar);

	ar_sdio->irq_data.irq_proc_reg =
		devm_kzalloc(ar->dev, sizeof(struct ath10k_sdio_irq_proc_regs),
			     GFP_KERNEL);
	if (!ar_sdio->irq_data.irq_proc_reg) {
		ret = -ENOMEM;
		goto err_core_destroy;
	}

	ar_sdio->irq_data.irq_en_reg =
		devm_kzalloc(ar->dev, sizeof(struct ath10k_sdio_irq_enable_regs),
			     GFP_KERNEL);
	if (!ar_sdio->irq_data.irq_en_reg) {
		ret = -ENOMEM;
		goto err_core_destroy;
	}

	ar_sdio->bmi_buf = devm_kzalloc(ar->dev, BMI_MAX_CMDBUF_SIZE, GFP_KERNEL);
	if (!ar_sdio->bmi_buf) {
		ret = -ENOMEM;
		goto err_core_destroy;
	}

	ar_sdio->func = func;
	sdio_set_drvdata(func, ar_sdio);

	ar_sdio->is_disabled = true;
	ar_sdio->ar = ar;

	spin_lock_init(&ar_sdio->lock);
	spin_lock_init(&ar_sdio->wr_async_lock);
	mutex_init(&ar_sdio->irq_data.mtx);

	INIT_LIST_HEAD(&ar_sdio->bus_req_freeq);
	INIT_LIST_HEAD(&ar_sdio->wr_asyncq);

	INIT_WORK(&ar_sdio->wr_async_work, ath10k_sdio_write_async_work);
	ar_sdio->workqueue = create_singlethread_workqueue("ath10k_sdio_wq");
	if (!ar_sdio->workqueue) {
		ret = -ENOMEM;
		goto err_core_destroy;
	}

	for (i = 0; i < ATH10K_SDIO_BUS_REQUEST_MAX_NUM; i++)
		ath10k_sdio_free_bus_req(ar, &ar_sdio->bus_req[i]);

	dev_id_base = FIELD_GET(QCA_MANUFACTURER_ID_BASE, id->device);
	switch (dev_id_base) {
	case QCA_MANUFACTURER_ID_AR6005_BASE:
	case QCA_MANUFACTURER_ID_QCA9377_BASE:
		ar->dev_id = QCA9377_1_0_DEVICE_ID;
		break;
	default:
		ret = -ENODEV;
		ath10k_err(ar, "unsupported device id %u (0x%x)\n",
			   dev_id_base, id->device);
		goto err_free_wq;
	}

	ar->id.vendor = id->vendor;
	ar->id.device = id->device;

	ath10k_sdio_set_mbox_info(ar);

	bus_params.dev_type = ATH10K_DEV_TYPE_HL;
	/* TODO: don't know yet how to get chip_id with SDIO */
	bus_params.chip_id = 0;
	bus_params.hl_msdu_ids = true;

	ret = ath10k_core_register(ar, &bus_params);
	if (ret) {
		ath10k_err(ar, "failed to register driver core: %d\n", ret);
		goto err_free_wq;
	}

	/* TODO: remove this once SDIO support is fully implemented */
	ath10k_warn(ar, "WARNING: ath10k SDIO support is work-in-progress, problems may arise!\n");

	return 0;

err_free_wq:
	destroy_workqueue(ar_sdio->workqueue);
err_core_destroy:
	ath10k_core_destroy(ar);

	return ret;
}