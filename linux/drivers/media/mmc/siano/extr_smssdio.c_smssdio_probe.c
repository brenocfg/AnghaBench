#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smssdio_device {int /*<<< orphan*/  coredev; struct sdio_func* func; } ;
struct smsdevice_params_t {int buffer_size; int num_buffers; scalar_t__ device_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  sendrequest_handler; int /*<<< orphan*/  devpath; struct smssdio_device* context; int /*<<< orphan*/ * device; } ;
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct sdio_device_id {int driver_data; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_DMA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMSSDIO_BLOCK_SIZE ; 
 int /*<<< orphan*/  SMS_DEVICE_FAMILY2 ; 
 scalar_t__ SMS_STELLAR ; 
 int /*<<< orphan*/  kfree (struct smssdio_device*) ; 
 struct smssdio_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct smsdevice_params_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int sdio_claim_irq (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 int sdio_enable_func (struct sdio_func*) ; 
 char* sdio_func_id (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int sdio_set_block_size (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct smssdio_device*) ; 
 TYPE_1__* sms_get_board (int) ; 
 int smscore_register_device (struct smsdevice_params_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smscore_set_board_id (int /*<<< orphan*/ ,int) ; 
 int smscore_start_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smscore_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smssdio_interrupt ; 
 int /*<<< orphan*/  smssdio_sendrequest ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int smssdio_probe(struct sdio_func *func,
			 const struct sdio_device_id *id)
{
	int ret;

	int board_id;
	struct smssdio_device *smsdev;
	struct smsdevice_params_t params;

	board_id = id->driver_data;

	smsdev = kzalloc(sizeof(struct smssdio_device), GFP_KERNEL);
	if (!smsdev)
		return -ENOMEM;

	smsdev->func = func;

	memset(&params, 0, sizeof(struct smsdevice_params_t));

	params.device = &func->dev;
	params.buffer_size = 0x5000;	/* ?? */
	params.num_buffers = 22;	/* ?? */
	params.context = smsdev;

	snprintf(params.devpath, sizeof(params.devpath),
		 "sdio\\%s", sdio_func_id(func));

	params.sendrequest_handler = smssdio_sendrequest;

	params.device_type = sms_get_board(board_id)->type;

	if (params.device_type != SMS_STELLAR)
		params.flags |= SMS_DEVICE_FAMILY2;
	else {
		/*
		 * FIXME: Stellar needs special handling...
		 */
		ret = -ENODEV;
		goto free;
	}

	ret = smscore_register_device(&params, &smsdev->coredev, GFP_DMA, NULL);
	if (ret < 0)
		goto free;

	smscore_set_board_id(smsdev->coredev, board_id);

	sdio_claim_host(func);

	ret = sdio_enable_func(func);
	if (ret)
		goto release;

	ret = sdio_set_block_size(func, SMSSDIO_BLOCK_SIZE);
	if (ret)
		goto disable;

	ret = sdio_claim_irq(func, smssdio_interrupt);
	if (ret)
		goto disable;

	sdio_set_drvdata(func, smsdev);

	sdio_release_host(func);

	ret = smscore_start_device(smsdev->coredev);
	if (ret < 0)
		goto reclaim;

	return 0;

reclaim:
	sdio_claim_host(func);
	sdio_release_irq(func);
disable:
	sdio_disable_func(func);
release:
	sdio_release_host(func);
	smscore_unregister_device(smsdev->coredev);
free:
	kfree(smsdev);

	return ret;
}