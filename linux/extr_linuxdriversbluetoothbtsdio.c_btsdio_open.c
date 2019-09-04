#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hci_dev {int /*<<< orphan*/  name; } ;
struct btsdio_data {TYPE_1__* func; } ;
struct TYPE_7__ {scalar_t__ class; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_EN_INTRD ; 
 int /*<<< orphan*/  REG_MD_SET ; 
 scalar_t__ SDIO_CLASS_BT_B ; 
 int /*<<< orphan*/  btsdio_interrupt ; 
 struct btsdio_data* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  sdio_claim_host (TYPE_1__*) ; 
 int sdio_claim_irq (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_disable_func (TYPE_1__*) ; 
 int sdio_enable_func (TYPE_1__*) ; 
 int /*<<< orphan*/  sdio_release_host (TYPE_1__*) ; 
 int /*<<< orphan*/  sdio_writeb (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btsdio_open(struct hci_dev *hdev)
{
	struct btsdio_data *data = hci_get_drvdata(hdev);
	int err;

	BT_DBG("%s", hdev->name);

	sdio_claim_host(data->func);

	err = sdio_enable_func(data->func);
	if (err < 0)
		goto release;

	err = sdio_claim_irq(data->func, btsdio_interrupt);
	if (err < 0) {
		sdio_disable_func(data->func);
		goto release;
	}

	if (data->func->class == SDIO_CLASS_BT_B)
		sdio_writeb(data->func, 0x00, REG_MD_SET, NULL);

	sdio_writeb(data->func, 0x01, REG_EN_INTRD, NULL);

release:
	sdio_release_host(data->func);

	return err;
}