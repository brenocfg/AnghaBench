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
struct atmel_sha_dev {int flags; int err; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int SHA_FLAGS_CPU ; 
 int SHA_FLAGS_DMA_ACTIVE ; 
 int SHA_FLAGS_DMA_READY ; 
 int SHA_FLAGS_OUTPUT_READY ; 
 int /*<<< orphan*/  atmel_sha_finish_req (int /*<<< orphan*/ ,int) ; 
 int atmel_sha_update_dma_start (struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  atmel_sha_update_dma_stop (struct atmel_sha_dev*) ; 

__attribute__((used)) static int atmel_sha_done(struct atmel_sha_dev *dd)
{
	int err = 0;

	if (SHA_FLAGS_CPU & dd->flags) {
		if (SHA_FLAGS_OUTPUT_READY & dd->flags) {
			dd->flags &= ~SHA_FLAGS_OUTPUT_READY;
			goto finish;
		}
	} else if (SHA_FLAGS_DMA_READY & dd->flags) {
		if (SHA_FLAGS_DMA_ACTIVE & dd->flags) {
			dd->flags &= ~SHA_FLAGS_DMA_ACTIVE;
			atmel_sha_update_dma_stop(dd);
			if (dd->err) {
				err = dd->err;
				goto finish;
			}
		}
		if (SHA_FLAGS_OUTPUT_READY & dd->flags) {
			/* hash or semi-hash ready */
			dd->flags &= ~(SHA_FLAGS_DMA_READY |
						SHA_FLAGS_OUTPUT_READY);
			err = atmel_sha_update_dma_start(dd);
			if (err != -EINPROGRESS)
				goto finish;
		}
	}
	return err;

finish:
	/* finish curent request */
	atmel_sha_finish_req(dd->req, err);

	return err;
}