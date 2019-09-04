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
struct gcm_sg_walk {unsigned int buf_bytes; unsigned int walk_bytes_remain; int /*<<< orphan*/  walk; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scatterwalk_advance (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_unmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gcm_sg_walk_done(struct gcm_sg_walk *gw, unsigned int bytesdone)
{
	int n;

	if (gw->ptr == NULL)
		return;

	if (gw->ptr == gw->buf) {
		n = gw->buf_bytes - bytesdone;
		if (n > 0) {
			memmove(gw->buf, gw->buf + bytesdone, n);
			gw->buf_bytes -= n;
		} else
			gw->buf_bytes = 0;
	} else {
		gw->walk_bytes_remain -= bytesdone;
		scatterwalk_unmap(&gw->walk);
		scatterwalk_advance(&gw->walk, bytesdone);
		scatterwalk_done(&gw->walk, 0, gw->walk_bytes_remain);
	}
}