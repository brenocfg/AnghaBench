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
typedef  int /*<<< orphan*/  u32 ;
struct qm_fd {int dummy; } ;
struct hp_handler {scalar_t__ addr; int /*<<< orphan*/  tx_mixer; int /*<<< orphan*/  rx_mixer; int /*<<< orphan*/ * frame_ptr; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HP_FIRST_WORD ; 
 int HP_NUM_WORDS ; 
 int /*<<< orphan*/  do_lfsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*,...) ; 
 scalar_t__ qm_fd_addr_get64 (struct qm_fd const*) ; 

__attribute__((used)) static inline int process_frame_data(struct hp_handler *handler,
				     const struct qm_fd *fd)
{
	u32 *p = handler->frame_ptr;
	u32 lfsr = HP_FIRST_WORD;
	int loop;

	if (qm_fd_addr_get64(fd) != handler->addr) {
		pr_crit("bad frame address, [%llX != %llX]\n",
			qm_fd_addr_get64(fd), handler->addr);
		return -EIO;
	}
	for (loop = 0; loop < HP_NUM_WORDS; loop++, p++) {
		*p ^= handler->rx_mixer;
		if (*p != lfsr) {
			pr_crit("corrupt frame data");
			return -EIO;
		}
		*p ^= handler->tx_mixer;
		lfsr = do_lfsr(lfsr);
	}
	return 0;
}