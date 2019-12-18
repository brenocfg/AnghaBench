#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ath6kl_sdio {int /*<<< orphan*/  dma_buffer_mutex; int /*<<< orphan*/  func; int /*<<< orphan*/ * dma_buffer; } ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HIF_BLOCK_BASIS ; 
 int /*<<< orphan*/  HIF_MBOX_BLOCK_SIZE ; 
 int HIF_READ ; 
 int HIF_WRITE ; 
 int ath6kl_sdio_io (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 
 struct ath6kl_sdio* ath6kl_sdio_priv (struct ath6kl*) ; 
 scalar_t__ buf_needs_bounce (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int round_down (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_sdio_read_write_sync(struct ath6kl *ar, u32 addr, u8 *buf,
				       u32 len, u32 request)
{
	struct ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	u8  *tbuf = NULL;
	int ret;
	bool bounced = false;

	if (request & HIF_BLOCK_BASIS)
		len = round_down(len, HIF_MBOX_BLOCK_SIZE);

	if (buf_needs_bounce(buf)) {
		if (!ar_sdio->dma_buffer)
			return -ENOMEM;
		mutex_lock(&ar_sdio->dma_buffer_mutex);
		tbuf = ar_sdio->dma_buffer;

		if (request & HIF_WRITE)
			memcpy(tbuf, buf, len);

		bounced = true;
	} else {
		tbuf = buf;
	}

	ret = ath6kl_sdio_io(ar_sdio->func, request, addr, tbuf, len);
	if ((request & HIF_READ) && bounced)
		memcpy(buf, tbuf, len);

	if (bounced)
		mutex_unlock(&ar_sdio->dma_buffer_mutex);

	return ret;
}