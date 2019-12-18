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
typedef  size_t u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct msix_entry {size_t vector; size_t entry; } ;
struct mic_irq {int dummy; } ;
struct mic_intr_cb {size_t cb_id; } ;
struct TYPE_3__ {int num_vectors; int* mic_msi_map; } ;
struct mic_device {struct pci_dev* pdev; TYPE_2__* intr_ops; TYPE_1__ irq_info; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
typedef  enum mic_intr_type { ____Placeholder_mic_intr_type } mic_intr_type ;
struct TYPE_4__ {int /*<<< orphan*/  (* program_msi_to_src_map ) (struct mic_device*,size_t,size_t,int) ;} ;

/* Variables and functions */
 int BIT (size_t) ; 
 int EINVAL ; 
 int ENOSPC ; 
 struct mic_irq* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mic_intr_cb*) ; 
 size_t MIC_NUM_OFFSETS ; 
 unsigned long MK_COOKIE (size_t,size_t) ; 
 int PTR_ERR (struct mic_intr_cb*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct msix_entry* mic_get_available_vector (struct mic_device*) ; 
 size_t mic_map_src_to_offset (struct mic_device*,int,int) ; 
 struct mic_intr_cb* mic_register_intr_callback (struct mic_device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pci_dev_msi_enabled (struct pci_dev*) ; 
 int request_threaded_irq (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,void*) ; 
 int /*<<< orphan*/  stub1 (struct mic_device*,size_t,size_t,int) ; 
 int /*<<< orphan*/  stub2 (struct mic_device*,size_t,size_t,int) ; 

struct mic_irq *
mic_request_threaded_irq(struct mic_device *mdev,
			 irq_handler_t handler, irq_handler_t thread_fn,
			 const char *name, void *data, int intr_src,
			 enum mic_intr_type type)
{
	u16 offset;
	int rc = 0;
	struct msix_entry *msix = NULL;
	unsigned long cookie = 0;
	u16 entry;
	struct mic_intr_cb *intr_cb;
	struct pci_dev *pdev = mdev->pdev;

	offset = mic_map_src_to_offset(mdev, intr_src, type);
	if (offset >= MIC_NUM_OFFSETS) {
		dev_err(&mdev->pdev->dev,
			"Error mapping index %d to a valid source id.\n",
			intr_src);
		rc = -EINVAL;
		goto err;
	}

	if (mdev->irq_info.num_vectors > 1) {
		msix = mic_get_available_vector(mdev);
		if (!msix) {
			dev_err(&mdev->pdev->dev,
				"No MSIx vectors available for use.\n");
			rc = -ENOSPC;
			goto err;
		}

		rc = request_threaded_irq(msix->vector, handler, thread_fn,
					  0, name, data);
		if (rc) {
			dev_dbg(&mdev->pdev->dev,
				"request irq failed rc = %d\n", rc);
			goto err;
		}
		entry = msix->entry;
		mdev->irq_info.mic_msi_map[entry] |= BIT(offset);
		mdev->intr_ops->program_msi_to_src_map(mdev,
				entry, offset, true);
		cookie = MK_COOKIE(entry, offset);
		dev_dbg(&mdev->pdev->dev, "irq: %d assigned for src: %d\n",
			msix->vector, intr_src);
	} else {
		intr_cb = mic_register_intr_callback(mdev, offset, handler,
						     thread_fn, data);
		if (IS_ERR(intr_cb)) {
			dev_err(&mdev->pdev->dev,
				"No available callback entries for use\n");
			rc = PTR_ERR(intr_cb);
			goto err;
		}

		entry = 0;
		if (pci_dev_msi_enabled(pdev)) {
			mdev->irq_info.mic_msi_map[entry] |= (1 << offset);
			mdev->intr_ops->program_msi_to_src_map(mdev,
				entry, offset, true);
		}
		cookie = MK_COOKIE(entry, intr_cb->cb_id);
		dev_dbg(&mdev->pdev->dev, "callback %d registered for src: %d\n",
			intr_cb->cb_id, intr_src);
	}
	return (struct mic_irq *)cookie;
err:
	return ERR_PTR(rc);
}