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
typedef  int u8 ;
struct dpaa_bp {int /*<<< orphan*/  (* free_buf_cb ) (struct dpaa_bp*,struct bm_buffer*) ;int /*<<< orphan*/  pool; } ;
struct bm_buffer {int dummy; } ;

/* Variables and functions */
 int bman_acquire (int /*<<< orphan*/ ,struct bm_buffer*,int) ; 
 int /*<<< orphan*/  stub1 (struct dpaa_bp*,struct bm_buffer*) ; 

__attribute__((used)) static void dpaa_bp_drain(struct dpaa_bp *bp)
{
	u8 num = 8;
	int ret;

	do {
		struct bm_buffer bmb[8];
		int i;

		ret = bman_acquire(bp->pool, bmb, num);
		if (ret < 0) {
			if (num == 8) {
				/* we have less than 8 buffers left;
				 * drain them one by one
				 */
				num = 1;
				ret = 1;
				continue;
			} else {
				/* Pool is fully drained */
				break;
			}
		}

		if (bp->free_buf_cb)
			for (i = 0; i < num; i++)
				bp->free_buf_cb(bp, &bmb[i]);
	} while (ret > 0);
}