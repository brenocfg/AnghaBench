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
typedef  int u32 ;
struct rcar_canfd_channel {int /*<<< orphan*/  base; } ;
struct canfd_frame {scalar_t__ data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int rcar_canfd_read (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_canfd_get_data(struct rcar_canfd_channel *priv,
				struct canfd_frame *cf, u32 off)
{
	u32 i, lwords;

	lwords = DIV_ROUND_UP(cf->len, sizeof(u32));
	for (i = 0; i < lwords; i++)
		*((u32 *)cf->data + i) =
			rcar_canfd_read(priv->base, off + (i * sizeof(u32)));
}