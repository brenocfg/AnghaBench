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
struct s5p_aes_dev {int /*<<< orphan*/  hash_flags; int /*<<< orphan*/  hash_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FLAGS_BUSY ; 
 int /*<<< orphan*/  HASH_FLAGS_DMA_ACTIVE ; 
 int /*<<< orphan*/  HASH_FLAGS_DMA_READY ; 
 int /*<<< orphan*/  HASH_FLAGS_OUTPUT_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5p_hash_finish_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_hash_handle_queue (struct s5p_aes_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5p_hash_update_dma_stop (struct s5p_aes_dev*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s5p_hash_tasklet_cb(unsigned long data)
{
	struct s5p_aes_dev *dd = (struct s5p_aes_dev *)data;

	if (!test_bit(HASH_FLAGS_BUSY, &dd->hash_flags)) {
		s5p_hash_handle_queue(dd, NULL);
		return;
	}

	if (test_bit(HASH_FLAGS_DMA_READY, &dd->hash_flags)) {
		if (test_and_clear_bit(HASH_FLAGS_DMA_ACTIVE,
				       &dd->hash_flags)) {
			s5p_hash_update_dma_stop(dd);
		}

		if (test_and_clear_bit(HASH_FLAGS_OUTPUT_READY,
				       &dd->hash_flags)) {
			/* hash or semi-hash ready */
			clear_bit(HASH_FLAGS_DMA_READY, &dd->hash_flags);
			goto finish;
		}
	}

	return;

finish:
	/* finish curent request */
	s5p_hash_finish_req(dd->hash_req, 0);

	/* If we are not busy, process next req */
	if (!test_bit(HASH_FLAGS_BUSY, &dd->hash_flags))
		s5p_hash_handle_queue(dd, NULL);
}