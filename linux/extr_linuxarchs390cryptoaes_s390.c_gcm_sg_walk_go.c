#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sg; } ;
struct gcm_sg_walk {unsigned int buf_bytes; unsigned int nbytes; scalar_t__ walk_bytes_remain; unsigned int walk_bytes; TYPE_1__ walk; int /*<<< orphan*/ * walk_ptr; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  scatterwalk_advance (TYPE_1__*,int) ; 
 void* scatterwalk_clamp (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  scatterwalk_done (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 void* scatterwalk_map (TYPE_1__*) ; 
 int /*<<< orphan*/  scatterwalk_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_unmap (TYPE_1__*) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gcm_sg_walk_go(struct gcm_sg_walk *gw, unsigned int minbytesneeded)
{
	int n;

	/* minbytesneeded <= AES_BLOCK_SIZE */
	if (gw->buf_bytes && gw->buf_bytes >= minbytesneeded) {
		gw->ptr = gw->buf;
		gw->nbytes = gw->buf_bytes;
		goto out;
	}

	if (gw->walk_bytes_remain == 0) {
		gw->ptr = NULL;
		gw->nbytes = 0;
		goto out;
	}

	gw->walk_bytes = scatterwalk_clamp(&gw->walk, gw->walk_bytes_remain);
	if (!gw->walk_bytes) {
		scatterwalk_start(&gw->walk, sg_next(gw->walk.sg));
		gw->walk_bytes = scatterwalk_clamp(&gw->walk,
						   gw->walk_bytes_remain);
	}
	gw->walk_ptr = scatterwalk_map(&gw->walk);

	if (!gw->buf_bytes && gw->walk_bytes >= minbytesneeded) {
		gw->ptr = gw->walk_ptr;
		gw->nbytes = gw->walk_bytes;
		goto out;
	}

	while (1) {
		n = min(gw->walk_bytes, AES_BLOCK_SIZE - gw->buf_bytes);
		memcpy(gw->buf + gw->buf_bytes, gw->walk_ptr, n);
		gw->buf_bytes += n;
		gw->walk_bytes_remain -= n;
		scatterwalk_unmap(&gw->walk);
		scatterwalk_advance(&gw->walk, n);
		scatterwalk_done(&gw->walk, 0, gw->walk_bytes_remain);

		if (gw->buf_bytes >= minbytesneeded) {
			gw->ptr = gw->buf;
			gw->nbytes = gw->buf_bytes;
			goto out;
		}

		gw->walk_bytes = scatterwalk_clamp(&gw->walk,
						   gw->walk_bytes_remain);
		if (!gw->walk_bytes) {
			scatterwalk_start(&gw->walk, sg_next(gw->walk.sg));
			gw->walk_bytes = scatterwalk_clamp(&gw->walk,
							gw->walk_bytes_remain);
		}
		gw->walk_ptr = scatterwalk_map(&gw->walk);
	}

out:
	return gw->nbytes;
}