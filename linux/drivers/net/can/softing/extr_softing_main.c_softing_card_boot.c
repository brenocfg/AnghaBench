#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_15__ {int up; int /*<<< orphan*/  lock; } ;
struct softing {int dpram_size; TYPE_5__ fw; TYPE_6__* pdev; TYPE_4__* pdat; int /*<<< orphan*/ * dpram; } ;
typedef  int /*<<< orphan*/  stream ;
struct TYPE_16__ {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  fw; } ;
struct TYPE_12__ {scalar_t__ addr; scalar_t__ offs; int /*<<< orphan*/  fw; } ;
struct TYPE_11__ {scalar_t__ addr; scalar_t__ offs; int /*<<< orphan*/  fw; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* reset ) (TYPE_6__*,int) ;int /*<<< orphan*/  (* enable_irq ) (TYPE_6__*,int) ;TYPE_3__ app; TYPE_2__ load; TYPE_1__ boot; } ;

/* Variables and functions */
 int EIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int const*,int) ; 
 int /*<<< orphan*/  memcpy_fromio (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,int const*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int softing_bootloader_command (struct softing*,int /*<<< orphan*/ ,char*) ; 
 int softing_chip_poweron (struct softing*) ; 
 int /*<<< orphan*/  softing_clr_reset_dpram (struct softing*) ; 
 int softing_load_app_fw (int /*<<< orphan*/ ,struct softing*) ; 
 int softing_load_fw (int /*<<< orphan*/ ,struct softing*,int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  softing_set_reset_dpram (struct softing*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int softing_card_boot(struct softing *card)
{
	int ret, j;
	static const uint8_t stream[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, };
	unsigned char back[sizeof(stream)];

	if (mutex_lock_interruptible(&card->fw.lock))
		return -ERESTARTSYS;
	if (card->fw.up) {
		mutex_unlock(&card->fw.lock);
		return 0;
	}
	/* reset board */
	if (card->pdat->enable_irq)
		card->pdat->enable_irq(card->pdev, 1);
	/* boot card */
	softing_set_reset_dpram(card);
	if (card->pdat->reset)
		card->pdat->reset(card->pdev, 1);
	for (j = 0; (j + sizeof(stream)) < card->dpram_size;
			j += sizeof(stream)) {

		memcpy_toio(&card->dpram[j], stream, sizeof(stream));
		/* flush IO cache */
		mb();
		memcpy_fromio(back, &card->dpram[j], sizeof(stream));

		if (!memcmp(back, stream, sizeof(stream)))
			continue;
		/* memory is not equal */
		dev_alert(&card->pdev->dev, "dpram failed at 0x%04x\n", j);
		ret = -EIO;
		goto failed;
	}
	wmb();
	/* load boot firmware */
	ret = softing_load_fw(card->pdat->boot.fw, card, card->dpram,
				card->dpram_size,
				card->pdat->boot.offs - card->pdat->boot.addr);
	if (ret < 0)
		goto failed;
	/* load loader firmware */
	ret = softing_load_fw(card->pdat->load.fw, card, card->dpram,
				card->dpram_size,
				card->pdat->load.offs - card->pdat->load.addr);
	if (ret < 0)
		goto failed;

	if (card->pdat->reset)
		card->pdat->reset(card->pdev, 0);
	softing_clr_reset_dpram(card);
	ret = softing_bootloader_command(card, 0, "card boot");
	if (ret < 0)
		goto failed;
	ret = softing_load_app_fw(card->pdat->app.fw, card);
	if (ret < 0)
		goto failed;

	ret = softing_chip_poweron(card);
	if (ret < 0)
		goto failed;

	card->fw.up = 1;
	mutex_unlock(&card->fw.lock);
	return 0;
failed:
	card->fw.up = 0;
	if (card->pdat->enable_irq)
		card->pdat->enable_irq(card->pdev, 0);
	softing_set_reset_dpram(card);
	if (card->pdat->reset)
		card->pdat->reset(card->pdev, 1);
	mutex_unlock(&card->fw.lock);
	return ret;
}