#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smssdio_device {TYPE_1__* func; } ;
struct sms_msg_data {int dummy; } ;
struct TYPE_4__ {size_t cur_blksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMSSDIO_DATA ; 
 int /*<<< orphan*/  sdio_claim_host (TYPE_1__*) ; 
 int sdio_memcpy_toio (TYPE_1__*,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  sdio_release_host (TYPE_1__*) ; 
 int /*<<< orphan*/  smsendian_handle_tx_message (struct sms_msg_data*) ; 

__attribute__((used)) static int smssdio_sendrequest(void *context, void *buffer, size_t size)
{
	int ret = 0;
	struct smssdio_device *smsdev;

	smsdev = context;

	sdio_claim_host(smsdev->func);

	smsendian_handle_tx_message((struct sms_msg_data *) buffer);
	while (size >= smsdev->func->cur_blksize) {
		ret = sdio_memcpy_toio(smsdev->func, SMSSDIO_DATA,
					buffer, smsdev->func->cur_blksize);
		if (ret)
			goto out;

		buffer += smsdev->func->cur_blksize;
		size -= smsdev->func->cur_blksize;
	}

	if (size) {
		ret = sdio_memcpy_toio(smsdev->func, SMSSDIO_DATA,
					buffer, size);
	}

out:
	sdio_release_host(smsdev->func);

	return ret;
}