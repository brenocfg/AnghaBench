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
struct bufdesc_prop {int dsize_log2; scalar_t__ base; } ;
struct bufdesc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int fec_enet_get_bd_index(struct bufdesc *bdp,
				 struct bufdesc_prop *bd)
{
	return ((const char *)bdp - (const char *)bd->base) >> bd->dsize_log2;
}