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
struct cobalt_stream {int /*<<< orphan*/  dma_channel; struct cobalt* cobalt; } ;
struct cobalt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT ; 
 int /*<<< orphan*/  CS_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int is_dma_done (struct cobalt_stream*) ; 

void omni_sg_dma_abort_channel(struct cobalt_stream *s)
{
	struct cobalt *cobalt = s->cobalt;

	if (is_dma_done(s) == false)
		iowrite32(ABORT, CS_REG(s->dma_channel));
}