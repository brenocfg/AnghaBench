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
struct s5p_aes_dev {scalar_t__ hash_sg_cnt; int /*<<< orphan*/  hash_flags; int /*<<< orphan*/  hash_sg_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FLAGS_DMA_READY ; 
 int /*<<< orphan*/  HASH_FLAGS_FINAL ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5p_hash_rx(struct s5p_aes_dev *dev)
{
	if (dev->hash_sg_cnt > 0) {
		dev->hash_sg_iter = sg_next(dev->hash_sg_iter);
		return 1;
	}

	set_bit(HASH_FLAGS_DMA_READY, &dev->hash_flags);
	if (test_bit(HASH_FLAGS_FINAL, &dev->hash_flags))
		return 0;

	return 2;
}