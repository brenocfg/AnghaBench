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
struct cm_dev {int /*<<< orphan*/ ** rx_buf; } ;

/* Variables and functions */
 int RIOCM_RX_RING_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void riocm_rx_free(struct cm_dev *cm)
{
	int i;

	for (i = 0; i < RIOCM_RX_RING_SIZE; i++) {
		if (cm->rx_buf[i] != NULL) {
			kfree(cm->rx_buf[i]);
			cm->rx_buf[i] = NULL;
		}
	}
}