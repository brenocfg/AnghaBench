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
typedef  scalar_t__ u64 ;
struct octeon_soft_command {int /*<<< orphan*/  node; int /*<<< orphan*/  size; scalar_t__ dma_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  head; int /*<<< orphan*/  alloc_buf_count; int /*<<< orphan*/  lock; } ;
struct octeon_device {TYPE_1__ sc_buf_pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_SOFT_COMMAND_BUFFERS ; 
 int /*<<< orphan*/  SOFT_COMMAND_BUFFER_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lio_dma_alloc (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  octeon_free_sc_buffer_pool (struct octeon_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int octeon_setup_sc_buffer_pool(struct octeon_device *oct)
{
	int i;
	u64 dma_addr;
	struct octeon_soft_command *sc;

	INIT_LIST_HEAD(&oct->sc_buf_pool.head);
	spin_lock_init(&oct->sc_buf_pool.lock);
	atomic_set(&oct->sc_buf_pool.alloc_buf_count, 0);

	for (i = 0; i < MAX_SOFT_COMMAND_BUFFERS; i++) {
		sc = (struct octeon_soft_command *)
			lio_dma_alloc(oct,
				      SOFT_COMMAND_BUFFER_SIZE,
					  (dma_addr_t *)&dma_addr);
		if (!sc) {
			octeon_free_sc_buffer_pool(oct);
			return 1;
		}

		sc->dma_addr = dma_addr;
		sc->size = SOFT_COMMAND_BUFFER_SIZE;

		list_add_tail(&sc->node, &oct->sc_buf_pool.head);
	}

	return 0;
}