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
typedef  size_t u32 ;
struct rcar_drif {TYPE_1__* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCAR_DRIF_BUF_DONE ; 
 int /*<<< orphan*/  RCAR_DRIF_BUF_OVERFLOW ; 
 size_t RCAR_DRIF_RFOVF ; 
 int /*<<< orphan*/  RCAR_DRIF_SISTR ; 
 size_t rcar_drif_read (struct rcar_drif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_drif_write (struct rcar_drif*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ unlikely (size_t) ; 

__attribute__((used)) static void rcar_drif_channel_complete(struct rcar_drif *ch, u32 idx)
{
	u32 str;

	ch->buf[idx].status |= RCAR_DRIF_BUF_DONE;

	/* Check for DRIF errors */
	str = rcar_drif_read(ch, RCAR_DRIF_SISTR);
	if (unlikely(str & RCAR_DRIF_RFOVF)) {
		/* Writing the same clears it */
		rcar_drif_write(ch, RCAR_DRIF_SISTR, str);

		/* Overflow: some samples are lost */
		ch->buf[idx].status |= RCAR_DRIF_BUF_OVERFLOW;
	}
}